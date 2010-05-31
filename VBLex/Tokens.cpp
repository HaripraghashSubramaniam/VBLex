// Tokens.cpp : CTokens �̎���

#include "stdafx.h"
#include "Tokens.h"


// CTokens


STDMETHODIMP CTokens::Item(VARIANT Index, VARIANT* pItem)
{
	VariantInit(pItem);

	// TODO:�����̌^��LONG�ɂ���
	if (Index.vt != VT_I4)
		return E_INVALIDARG;

	// �����ȃC���f�b�N�X�̓G���[�ɂ���
	if (Index.lVal > m_vector.size() || Index.lVal <= 0)
		return E_INVALIDARG;

	// Token�I�u�W�F�N�g��IDispatch�C���^�[�t�F�[�X��Ԃ�
	pItem->vt = VT_DISPATCH;
	IToken* pToken = m_vector.at(Index.lVal);
	return pToken->QueryInterface(IID_IDispatch, (void**) &(pItem->pdispVal));
}

STDMETHODIMP CTokens::get_Count(LONG* pVal)
{
	*pVal = m_vector.size();
	return S_OK;
}

STDMETHODIMP CTokens::get__NewEnum(LPUNKNOWN* pVal)
{
	// �ꎞ�I�Ȕz��𐶐�
	VARIANT* var = new VARIANT[m_vector.size()];
	std::vector<IToken*>::iterator it;
	int i = 0;
	for (it = m_vector.begin(); it != m_vector.end(); it++, i++)
	{
		VariantInit(&var[i]);
		var[i].vt = VT_DISPATCH;
		(*it)->QueryInterface(IID_IDispatch, (void**) &(var[i].pdispVal));
	}

	// �ǂ݂₷�����邽��ifdef
	typedef CComObject< CComEnum< IEnumVARIANT,
									&IID_IEnumVARIANT,
									VARIANT,
									_Copy<VARIANT> > > EnumVar;

	// �񋓎q��������
	EnumVar* pVar = new EnumVar;
	pVar->Init(&var[0], &var[i], NULL, AtlFlagCopy);

	// �ꎞ�I�Ȕz����J��
	for (i = 0; i < m_vector.size(); i++)
		VariantClear(&var[i]);

	delete[] var;

	// �񋓎q��IUnknown��Ԃ�
	pVar->QueryInterface(IID_IUnknown, (void**)pVal);

	return S_OK;
}

STDMETHODIMP CTokens::Add(IToken* pToken)
{
	m_vector.push_back(pToken);
	pToken->AddRef();

	return S_OK;
}
