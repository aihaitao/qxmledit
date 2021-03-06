/**************************************************************************
 *  This file is part of QXmlEdit                                         *
 *  Copyright (C) 2018 by Luca Bellonda and individual contributors       *
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

#include "editingtypesdialog.h"
#include "ui_editingtypesdialog.h"
#include "applicationdata.h"
#include "utils.h"

EditingTypesDialog::EditingTypesDialog(ApplicationData *data, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::EditingTypesDialog)
{
    _data = data ;
    ui->setupUi(this);
    if(_data->isBaseEditModeForm()) {
        ui->optionForm->setChecked(true);
    } else {
        ui->optionText->setChecked(true);
    }
}

EditingTypesDialog::~EditingTypesDialog()
{
    delete ui;
}

void EditingTypesDialog::accept()
{
    _data->setBaseEditModeForm(ui->optionForm->isChecked());
    QDialog::accept();
}

void EditingTypesDialog::on_cmdPredefined_clicked()
{
    _data->setBaseEditModeForm(true);
    QDialog::accept();
}
