// Tokenizer.h : CTokenizer �̐錾

#pragma once
#include "resource.h"       // ���C�� �V���{��
#include "Tokens.h"
#include "VBLex_i.h"


#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "DCOM �̊��S�T�|�[�g���܂�ł��Ȃ� Windows Mobile �v���b�g�t�H�[���̂悤�� Windows CE �v���b�g�t�H�[���ł́A�P��X���b�h COM �I�u�W�F�N�g�͐������T�|�[�g����Ă��܂���BATL ���P��X���b�h COM �I�u�W�F�N�g�̍쐬���T�|�[�g���邱�ƁA����т��̒P��X���b�h COM �I�u�W�F�N�g�̎����̎g�p�������邱�Ƃ���������ɂ́A_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA ���`���Ă��������B���g�p�� rgs �t�@�C���̃X���b�h ���f���� 'Free' �ɐݒ肳��Ă���ADCOM Windows CE �ȊO�̃v���b�g�t�H�[���ŃT�|�[�g�����B��̃X���b�h ���f���Ɛݒ肳��Ă��܂����B"
#endif



// CTokenizer

class ATL_NO_VTABLE CTokenizer :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CTokenizer, &CLSID_Tokenizer>,
	public IDispatchImpl<ITokenizer, &IID_ITokenizer, &LIBID_VBLexLib, /*wMajor =*/ 1, /*wMinor =*/ 0>
{
public:
	CTokenizer()
	{
	}

DECLARE_REGISTRY_RESOURCEID(IDR_TOKENIZER)


BEGIN_COM_MAP(CTokenizer)
	COM_INTERFACE_ENTRY(ITokenizer)
	COM_INTERFACE_ENTRY(IDispatch)
END_COM_MAP()



	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		HRESULT hr;

		// Create tokens collection 
		CComObject<CTokens>* pTokens;
		hr = CComObject<CTokens>::CreateInstance(&pTokens);
		if (FAILED(hr))
			return hr;

		m_tokens = pTokens;

		return S_OK;
	}

	void FinalRelease()
	{
	}

public:

	STDMETHOD(get_SourceText)(BSTR* pVal);
	STDMETHOD(put_SourceText)(BSTR newVal);
	STDMETHOD(get_Tokens)(LPDISPATCH* pVal);
	STDMETHOD(get_Version)(BSTR* pVal){
		CComBSTR ver("Version 0.1");
		ver.CopyTo(pVal);
		return S_OK;
	}

private:

	CComBSTR m_sourceText;
	CComPtr<ITokens> m_tokens;

};

OBJECT_ENTRY_AUTO(__uuidof(Tokenizer), CTokenizer)
