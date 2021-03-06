/*
DialogTab03.cpp

MIT License

Copyright(c) 2018 eliboa

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files(the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and / or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions :

The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.

*/
//

#include "stdafx.h"
#include "TegraRcmGUI.h"
#include "DialogTab03.h"
#include "afxdialogex.h"


// DialogTab03 dialog

IMPLEMENT_DYNAMIC(DialogTab03, CDialogEx)

DialogTab03::DialogTab03(TegraRcm *pTegraRcm, CWnd* Parent /*=NULL*/)
	: CDialogEx(ID_DIALOGTAB_03, Parent)
{
	m_TegraRcm = pTegraRcm;
}

DialogTab03::~DialogTab03()
{
}

void DialogTab03::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}


BOOL DialogTab03::OnInitDialog()
{
	CDialog::OnInitDialog();
	
	string value = m_TegraRcm->GetPreset("AUTO_INJECT");
	if (value == "TRUE")
	{
		m_TegraRcm->AUTOINJECT_CURR = TRUE;
		CMFCButton*checkbox = (CMFCButton*)GetDlgItem(AUTO_INJECT);
		checkbox->SetCheck(BST_CHECKED);
	}

	value = m_TegraRcm->GetPreset("MIN_TO_TRAY");
	if (value == "TRUE")
	{
		m_TegraRcm->MIN_TO_TRAY_CURR = TRUE;
		CMFCButton*checkbox = (CMFCButton*)GetDlgItem(MIN_TO_TRAY);
		checkbox->SetCheck(BST_CHECKED);
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // EXCEPTION: OCX Property Pages should return FALSE
}

BEGIN_MESSAGE_MAP(DialogTab03, CDialogEx)
	ON_BN_CLICKED(AUTO_INJECT, &DialogTab03::OnClickedAutoInject)
	ON_BN_CLICKED(MIN_TO_TRAY, &DialogTab03::OnClickedMinToTray)
	ON_BN_CLICKED(ID_INSTALL_DRIVER, &DialogTab03::OnBnClickedInstallDriver)
END_MESSAGE_MAP()


// DialogTab03 message handlers


void DialogTab03::OnClickedAutoInject()
{
	// Get Auto inject checkbox value (checked, unchecked)
	CButton *m_ctlCheck = (CButton*)GetDlgItem(AUTO_INJECT);
	BOOL IsCheckChecked = (m_ctlCheck->GetCheck() == 1) ? true : false;

	if (m_TegraRcm->AUTOINJECT_CURR != IsCheckChecked)
	{
		// Auto inject option enabled
		if (IsCheckChecked)
		{
			m_TegraRcm->SetPreset("AUTO_INJECT", "TRUE");
			m_TegraRcm->DELAY_AUTOINJECT = TRUE;
		}
		// Auto inject option disabled
		else
		{
			m_TegraRcm->SetPreset("AUTO_INJECT", "FALSE");
			m_TegraRcm->DELAY_AUTOINJECT = FALSE;
		}
		// Save current checkbox value
		m_TegraRcm->AUTOINJECT_CURR = IsCheckChecked;
	}
}


void DialogTab03::OnClickedMinToTray()
{
	// Get Minimize to tray checkbox value (checked, unchecked)
	CButton *m_ctlCheck = (CButton*)GetDlgItem(MIN_TO_TRAY);
	BOOL IsCheckChecked = (m_ctlCheck->GetCheck() == 1) ? true : false;
	if (m_TegraRcm->MIN_TO_TRAY_CURR != IsCheckChecked)
	{
		if (IsCheckChecked) m_TegraRcm->SetPreset("MIN_TO_TRAY", "TRUE");
		else m_TegraRcm->SetPreset("MIN_TO_TRAY", "FALSE");
		m_TegraRcm->MIN_TO_TRAY_CURR = IsCheckChecked;
	}
}


void DialogTab03::OnBnClickedInstallDriver()
{
	m_TegraRcm->InstallDriver();
}

