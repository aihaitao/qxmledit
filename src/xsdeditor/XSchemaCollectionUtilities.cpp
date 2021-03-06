/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2013-2018 by Luca Bellonda and individual contributors  *
 *    as indicated in the AUTHORS file                                    *
 *  lbellonda _at_ gmail.com                                              *
 *                                                                        *
 * This library is free software; you can redistribute it and/or          *
 * modify it under the terms of the GNU Library General Public            *
 * License as published by the Free Software Foundation; either           *
 * version 2 of the License, or (at your option) any later version.       *
 *                                                                        *
 * This library is distributed in the hope that it will be useful,        *
 * but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU      *
 * Library General Public License for more details.                       *
 *                                                                        *
 * You should have received a copy of the GNU Library General Public      *
 * License along with this library; if not, write to the                  *
 * Free Software Foundation, Inc., 51 Franklin Street, Fifth Floor,       *
 * Boston, MA  02110-1301  USA                                            *
 **************************************************************************/

#include "xsdeditor/xschema.h"
#include "xsdeditor/xsddefinitions.h"
#include "xsdeditor/XSchemaIOContants.h"
#include "utils.h"

//------------------------------------

AttrCollectInfo::AttrCollectInfo()
{
    isReference = false ;
    attribute = NULL ;
    attributeGroup = NULL ;
    originalAttributeGroup = NULL ;
    isTypeRestriction = false ;
    isTypeExtension = false ;
    originalAttribute = NULL ;
    isSimpleUnion = false ;
    isSimpleList = false ;
}


AttrCollectInfo::~AttrCollectInfo()
{
}

bool AttrCollectInfo::isGroup()
{
    return attributeGroup != NULL ;
}

//------------------------------------

XSchemaAttributesCollection::XSchemaAttributesCollection()
{
    collectGroups = false;
}

XSchemaAttributesCollection::~XSchemaAttributesCollection()
{
    foreach(AttrCollectInfo* attr, attributes.values()) {
        delete attr;
    }
    attributes.clear();
}

void XSchemaAttributesCollection::insert(const QString &name, XSchemaAttribute* finalAttribute, const QString &parTypeName, QStringList parEnums, const QString &defaultValue, XSchemaAttribute* originalAttribute)
{
    AttrCollectInfo *info = new AttrCollectInfo();
    info->attribute = finalAttribute ;
    info->type = parTypeName ;
    info->enums = parEnums;
    info->defaultValue = defaultValue ;
    info->originalAttribute = originalAttribute ;
    if(attributes.contains(name)) {
        delete attributes[name];
        attributes.remove(name);
    }
    attributes.insert(name, info);
}

void XSchemaAttributesCollection::insertGroup(const QString &name, XSchemaAttributeGroup* originalGroup, XSchemaAttributeGroup* finalGroup)
{
    AttrCollectInfo *info = new AttrCollectInfo();
    info->attributeGroup = finalGroup ;
    info->originalAttributeGroup = originalGroup ;
    attributes.insert(name, info);
}

//------------------------------------

void XSchemaXmlRepresentationInfo::setAttributes(XSchemaAttributesCollection &attributesCollection)
{
    foreach(QString name, attributesCollection.attributes.keys()) {
        AttrCollectInfo* attr = attributesCollection.attributes[name];
        QString value ;
        if(attr->enums.isEmpty()) {
            if(!attr->defaultValue.isEmpty()) {
                value = attr->defaultValue ;
            } else {
                value = attr->type ;
            }
        } else {
            bool isFirst = true;
            if(!attr->defaultValue.isEmpty()) {
                value = attr->defaultValue ;
                value += " " ;
                isFirst = false ;
            }

            foreach(QString s, attr->enums) {
                if(isFirst) {
                    isFirst = false ;
                } else {
                    value += "|" ;
                }
                value += s ;
            }
        }
        attributes.insert(name, value);
    }
}

QString XSchemaXmlRepresentationInfo::buildXmlRepresentation()
{
    QDomDocument document ;
    QDomElement element = document.createElement(tag);
    foreach(QString name, attributes.keys()) {
        QString value = attributes[name];
        element.setAttribute(name, value);
    }
    document.appendChild(element);
    QString result =  document.toString(4);
    return result;
}

//------------------------------------


