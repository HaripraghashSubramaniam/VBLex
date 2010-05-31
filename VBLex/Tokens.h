// Tokens.h : CTokens �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��
#include <vector>
#include "VBLex_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif



// CTokens

class ATL_NO_VTABLE CTokens :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTokens, &CLSID_Tokens>,
	public IDispatchImpl<ITokens, &IID_ITokens, &LIBID_VBLexLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTokens()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TOKENS)


BEGIN_COM_MAP(CTokens)
	COM_INTERFACE_ENTRY(ITokens)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{
		// vector�̃I�u�W�F�N�g���J��
		std::vector<IToken*>::iterator it;
		for (it = m_vector.begin(); it != m_vector.end(); it++)
			(*it)->Release();
	}

public:

	STDMETHOD(Item)(VARIANT Index, VARIANT* pItem);
	STDMETHOD(Add)(IToken* pToken);
	STDMETHOD(get_Count)(LONG* pVal);
	STDMETHOD(get__NewEnum)(LPUNKNOWN* pVal);

private:

	std::vector<IToken*> m_vector;
	
};

OBJECT_ENTRY_AUTO(__uuidof(Tokens), CTokens)
