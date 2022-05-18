
#include <windows.h>
#include <shlobj.h>
#include <shlwapi.h>
#include <strsafe.h>
#include "BFFileAndFolderDialog.h"
#include <new>
#include <QStringList>
#include <QGuiApplication>
#include <QWindow>

QStringList s_result_path_list;	//对话框选择结果路径
bool s_b_init;					//对话框初始化

const DWORD c_idAdd = 601;		//自定义导入按钮标识符
const DWORD c_idDone = 602;		//

HRESULT GetIDListName(IShellItem *psi, PWSTR *ppsz) {
  *ppsz = NULL;
  HRESULT hr = E_FAIL;

  WCHAR szFullName[2048];
  szFullName[0] = 0;
  PWSTR pszOutput = szFullName;
  size_t cchOutput = ARRAYSIZE(szFullName);

  PWSTR pszName;
  hr = psi->GetDisplayName(SIGDN_FILESYSPATH, &pszName);
  if (SUCCEEDED(hr)) {
    s_result_path_list.append(QString::fromStdWString(pszName));
  }

  return hr;
}

HRESULT GetSelectionFromSite(IUnknown *punkSite, BOOL fNoneImpliesFolder,
                             IShellItemArray **ppsia) {
  *ppsia = NULL;
  IFolderView2 *pfv;
  HRESULT hr =
      IUnknown_QueryService(punkSite, SID_SFolderView, IID_PPV_ARGS(&pfv));
  if (SUCCEEDED(hr)) {
    hr = pfv->GetSelection(fNoneImpliesFolder, ppsia);
    pfv->Release();
  }
  return hr;
}

void ReportSelectedItems(IUnknown *punkSite, IShellItemArray *psia) {
  DWORD cItems;
  HRESULT hr = psia->GetCount(&cItems);
  for (DWORD i = 0; SUCCEEDED(hr) && (i < cItems); i++) {
    IShellItem *psi;
    hr = psia->GetItemAt(i, &psi);
    if (SUCCEEDED(hr)) {
      PWSTR pszName;
      hr = GetIDListName(psi, &pszName);
      psi->Release();
    }
  }
}

void ReportSelectedItemsFromSite(IUnknown *punkSite) {
  IShellItemArray *psia;
  HRESULT hr = GetSelectionFromSite(punkSite, false, &psia);
  if (SUCCEEDED(hr)) {
    ReportSelectedItems(punkSite, psia);
    psia->Release();
  }
}

/* Picking Files and Folders in Basket Mode
 * **************************************************************************************/

class CPickFilesAndFoldersCallback : public IFileDialogEvents,
                                     public IFileDialogControlEvents {
 public:
  CPickFilesAndFoldersCallback() {}

  // IUnknown
  IFACEMETHODIMP QueryInterface(REFIID riid, void **ppv) {
    static const QITAB qit[] = {
        QITABENT(CPickFilesAndFoldersCallback, IFileDialogEvents),
        QITABENT(CPickFilesAndFoldersCallback, IFileDialogControlEvents),
        {0},
    };
    return QISearch(this, qit, riid, ppv);
  }

  // This class makes special assumptions about how it is used, specifically
  // 1) This class will only reside on the stack.
  // 2) Components that consume this object have well-defined reference
  // lifetimes.
  //    In this case, this is only consumed by the file dialog advise and
  //    unadvise. Unadvising will release the file dialog's only reference to
  //    this object.
  //
  // Do not do this for heap allocated objects.
  IFACEMETHODIMP_(ULONG) AddRef() { return 3; }
  IFACEMETHODIMP_(ULONG) Release() { return 2; }

  // IFileDialogEvents
  IFACEMETHODIMP OnFileOk(IFileDialog *pfd) {
    ReportSelectedItemsFromSite(pfd);
    return S_OK;  // S_FALSE keeps the dialog up, return S_OK to allows it to
                     // dismiss
  }

  IFACEMETHODIMP OnFolderChanging(IFileDialog *  pfd ,
                                  IShellItem * /* psi */) {
    if (s_b_init) {
      s_b_init = false;

      IOleWindow *pWindow = NULL;
      HRESULT hr = pfd->QueryInterface(IID_PPV_ARGS(&pWindow));
      if (SUCCEEDED(hr)) {
        HWND hwndDialog;
        hr = pWindow->GetWindow(&hwndDialog);
        HWND openButton = GetDlgItem(hwndDialog, IDOK);
        SetWindowTextW(openButton, L"导入");
        RECT rect;
        GetWindowRect(openButton, &rect);
        ShowWindow(openButton, SW_HIDE);
        pWindow->Release();
      }
    }
    return S_OK;
  }

  IFACEMETHODIMP OnFolderChange(IFileDialog *  pfd ) {
    return S_OK;
  }

  IFACEMETHODIMP OnSelectionChange(IFileDialog *pfd) {
    return S_OK;
  }

  IFACEMETHODIMP OnShareViolation(
      IFileDialog * /* pfd */, IShellItem * /* psi */,
      FDE_SHAREVIOLATION_RESPONSE * /* pResponse */) {
    return E_NOTIMPL;
  }
  IFACEMETHODIMP OnTypeChange(IFileDialog * /* pfd */) { return E_NOTIMPL; }
  IFACEMETHODIMP OnOverwrite(IFileDialog * /* pfd */, IShellItem * /* psi */,
                             FDE_OVERWRITE_RESPONSE * /* pResponse */) {
    return E_NOTIMPL;
  }

  // IFileDialogControlEvents
  IFACEMETHODIMP OnItemSelected(IFileDialogCustomize * /* pfdc */,
                                DWORD /* dwIDCtl */, DWORD /* dwIDItem */) {
    return E_NOTIMPL;
  }

  IFACEMETHODIMP OnButtonClicked(IFileDialogCustomize *pfdc, DWORD dwIDCtl) {
    switch (dwIDCtl) {
      case c_idAdd: {
        // Instead of using IFileDialog::GetCurrentSelection(), we need to get
        // the selection from the view to handle the "no selection implies
        // folder" case
        ReportSelectedItemsFromSite(pfdc);
        IFileDialog *pfd;
        if (SUCCEEDED(pfdc->QueryInterface(&pfd))) {
          pfd->Close(S_OK);
          pfd->Release();
          break;
        }
      }
      case c_idDone: {
        IFileDialog *pfd;
        if (SUCCEEDED(pfdc->QueryInterface(&pfd))) {
          pfd->Close(S_OK);
          pfd->Release();
        }
      } break;

      default:
        break;
    }

    return S_OK;
  }

  IFACEMETHODIMP OnCheckButtonToggled(IFileDialogCustomize * /* pfdc */,
                                      DWORD /* dwIDCtl */,
                                      BOOL /* bChecked */) {
    return E_NOTIMPL;
  }
  IFACEMETHODIMP OnControlActivating(IFileDialogCustomize * /* pfdc */,
                                     DWORD /* dwIDCtl */) {
    return E_NOTIMPL;
  }
};

void InitData() {
  s_result_path_list.clear();
  s_b_init = true;
}

void PickFilesAndFolders(QWidget *widget, const QString &title,
                         const QString &dir ) {
  InitData();

  IFileOpenDialog *pfd;
  if (SUCCEEDED(CoCreateInstance(CLSID_FileOpenDialog, NULL,
                                 CLSCTX_INPROC_SERVER, IID_PPV_ARGS(&pfd)))) {
    CPickFilesAndFoldersCallback foacb;
    DWORD dwCookie;
    if (SUCCEEDED(pfd->Advise(&foacb, &dwCookie))) {
      DWORD dwOptions;
      if (SUCCEEDED(pfd->GetOptions(&dwOptions))) {
        pfd->SetOptions(dwOptions | FOS_ALLOWMULTISELECT |
                        FOS_ALLNONSTORAGEITEMS);
      }

      IFileDialogCustomize *pfdc;
      if (SUCCEEDED(pfd->QueryInterface(&pfdc))) {
        // The spacing pads the button a bit.
        pfdc->AddPushButton(c_idAdd, L"导入");
        pfdc->Release();
      }

      IFileDialog2 *pfd2;
      if (SUCCEEDED(pfd->QueryInterface(&pfd2))) {
        pfd2->SetCancelButtonLabel(L"取消");
        pfd2->Release();
      } else {
        // pre Win7 we need to add a 3rd button, ugly but workable
        IFileDialogCustomize *pfdc;
        if (SUCCEEDED(pfd->QueryInterface(&pfdc))) {
          pfdc->AddPushButton(c_idDone, L"取消");
          pfdc->Release();
        }
      }

	  if (!title.isEmpty()) {
        QString tmp_title = title;
            pfd->SetTitle((const wchar_t *)tmp_title.utf16());
      }
      // the items selected are passed back via OnFileOk()
      // so we don't process the results of the dialog
      HRESULT ret;
      if (widget) {
        QWindow *wid = widget->windowHandle();
        if (wid) {
        } else {
          wid = QGuiApplication::focusWindow();
        }
        HRESULT ret = pfd->Show((HWND)(wid->winId()));
      } else {
        HRESULT ret = pfd->Show(NULL);  // hr intentionally ignored
	  }
      pfd->Unadvise(dwCookie);
    }
    pfd->Release();
  }
}
