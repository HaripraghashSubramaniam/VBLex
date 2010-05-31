// Token.h : CToken �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��
#include <string>

#include "VBLex_i.h"

using namespace std;

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif



// CToken

class ATL_NO_VTABLE CToken :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CToken, &CLSID_Token>,
	public IDispatchImpl<IToken, &IID_IToken, &LIBID_VBLexLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CToken()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TOKEN)


BEGIN_COM_MAP(CToken)
	COM_INTERFACE_ENTRY(IToken)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(get_Text)(BSTR* pVal) {
		m_text.CopyTo(pVal);
		return S_OK;
	}

	STDMETHOD(put_Text)(BSTR newVal) {
		m_text.Empty();
		m_text.AppendBSTR(newVal);
		return S_OK;
	}

	STDMETHOD(get_Type)(LONG* pVal) {
		*pVal = m_type;
		return S_OK;
	}

	STDMETHOD(put_Type)(LONG newVal) {
		m_type = newVal;
		return S_OK;
	}

	STDMETHOD(Init)(BSTR text, LONG _type) {
		m_text.Empty();
		m_text.AppendBSTR(text);

		m_type = _type;

		return S_OK;
	}

private:
	CComBSTR m_text;
	LONG	 m_type;

public:
};

OBJECT_ENTRY_AUTO(__uuidof(Token), CToken)
