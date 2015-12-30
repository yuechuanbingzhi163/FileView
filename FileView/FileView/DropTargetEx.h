#ifndef DROP_TARGET_EX_H
#define DROP_TARGET_EX_H

#include "stdafx.h"

#include "OleIdl.h"
#include "ShObjIdl.h"
#include <shellapi.h>

#define WM_DRAG_FILE_INTO_TARGET			(WM_USER + 0X8888)

typedef struct _DRAGDATA
{
	int cfFormat;
	STGMEDIUM stgMedium;
}DRAGDATA,*LPDRAGDATA;

class CDropTargetEx : public IDropTarget
{
public:
	CDropTargetEx();
	virtual ~CDropTargetEx();

	BOOL DragDropRegister(HWND hWnd,DWORD AcceptKeyState = MK_LBUTTON);

	void AddTargetControl(CControlUI *pControl);

	HRESULT STDMETHODCALLTYPE QueryInterface(REFIID iid, void ** ppvObject);

	ULONG STDMETHODCALLTYPE AddRef(void);

	ULONG STDMETHODCALLTYPE Release(void);

	HRESULT STDMETHODCALLTYPE DragOver(DWORD grfKeyState,POINTL pt,	DWORD *pdwEffect);

	HRESULT STDMETHODCALLTYPE DragEnter(IDataObject * pDataObject,DWORD grfKeyState, POINTL pt,	DWORD * pdwEffect);

	HRESULT STDMETHODCALLTYPE DragLeave(void);

	HRESULT STDMETHODCALLTYPE Drop(IDataObject *pDataObj,DWORD grfKeyState,	POINTL pt,	DWORD __RPC_FAR *pdwEffect);

	BOOL GetDragData(IDataObject *pDataObject,FORMATETC cFmt);	

	void ProcessDrop(LPDRAGDATA pDropData/*HDROP hDrop*/, POINT pt);

	//枚举数据格式的函数，我这里并没有用到，但是将来可能会用,函数目前只枚举了HDROP类型
	BOOL EnumDragData(IDataObject *pDataObject);

private:	
	HWND	m_hTargetWnd;
	list<CControlUI*> m_listTargetControls;

	ULONG	tb_RefCount;	
	DWORD	m_AcceptKeyState;

	bool	m_bUseDnDHelper;
	IDropTargetHelper* m_piDropHelper;

	vector<LPDRAGDATA> m_Array;
};
#endif	//DROP_TARGET_EX_H