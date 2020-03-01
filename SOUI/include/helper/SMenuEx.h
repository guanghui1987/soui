﻿#pragma once

#include <core/shostwnd.h>

namespace SOUI
{
    class SMenuEx;
    class SOUI_EXP SMenuExItem : public SWindow
    {
        SOUI_CLASS_NAME(SMenuExItem,L"menuItem")
    public:
        SMenuExItem(SMenuEx *pOwnerMenu,ISkinObj *pItemSkin);

        ~SMenuExItem();

        SMenuEx * GetSubMenu();

        SMenuEx * GetOwnerMenu();

        void HideSubMenu();

        void ShowSubMenu(BOOL bCheckFirstItem);

        WCHAR GetHotKey() const;

        void OnSubMenuHided(BOOL bUncheckItem);
    protected:
        virtual BOOL CreateChildren(pugi::xml_node xmlNode);

        virtual CSize GetDesiredSize(LPCRECT pRcContainer);

        virtual void GetTextRect(LPRECT pRect);


    protected:

        BOOL OnEraseBkgnd(IRenderTarget *pRT);

        void OnPaint(IRenderTarget *pRT);

        SOUI_MSG_MAP_BEGIN()
            MSG_WM_ERASEBKGND_EX(OnEraseBkgnd)
            MSG_WM_PAINT_EX(OnPaint)
        SOUI_MSG_MAP_END()

    protected:
        SOUI_ATTRS_BEGIN()
			ATTR_SKIN(L"iconSkin", m_pIconSkin, FALSE)
            ATTR_INT(L"icon",m_iIcon,TRUE)
            ATTR_INT(L"check",m_bCheck,TRUE)
            ATTR_INT(L"radio",m_bRadio,TRUE)
            ATTR_CHAR(L"hotKey",m_cHotKey,FALSE)
        SOUI_ATTRS_END()

        SMenuEx * m_pSubMenu;
        SMenuEx * m_pOwnerMenu;
		ISkinObj * m_pIconSkin;
        int       m_iIcon;
        BOOL      m_bCheck;
        BOOL      m_bRadio;    
        WCHAR     m_cHotKey;
    };

    class SOUI_EXP SMenuEx : protected SHostWnd
    {
        friend class SMenuExItem;
        friend class SMenuExRunData;
    public:
        SMenuEx(void);
        virtual ~SMenuEx(void);

        BOOL LoadMenu(LPCTSTR pszMenu);
        BOOL LoadMenu(pugi::xml_node xmlNode);

        UINT TrackPopupMenu(UINT flag,int x,int y,HWND hOwner,int nScale = 100);
		static void ExitPopupMenu(int nCmdId=0);

        SMenuExItem * GetParentItem() {return m_pParent;}
        SMenuEx * GetSubMenu(int nID);
        SMenuExItem * GetMenuItem(int nID);

		DWORD GetContextHelpId() const;

		void SetContextHelpId(DWORD dwId);
		BOOL InsertMenu(UINT uPos,UINT uFlag,int nId,LPCTSTR lpNewItem);
    protected:
        int OnMouseActivate(HWND wndTopLevel, UINT nHitTest, UINT message);
        void OnTimer(UINT_PTR timeID);
        void OnKeyDown(UINT nChar, UINT nRepCnt, UINT nFlags);

        BEGIN_MSG_MAP_EX(SMenuEx)
            MSG_WM_MOUSEACTIVATE(OnMouseActivate)
            MSG_WM_TIMER(OnTimer)
            MSG_WM_KEYDOWN(OnKeyDown)
            CHAIN_MSG_MAP(SHostWnd)
        END_MSG_MAP()
    protected:
        virtual BOOL _HandleEvent(EventArgs *pEvt);
		virtual const SStringW & GetTranslatorContext();
		virtual int GetScale() const;

        void ShowMenu(UINT uFlag,int x,int y);
        void HideMenu(BOOL bUncheckParentItem);
        void HideSubMenu();
        void RunMenu(HWND hOwner);

        void PopupSubMenu(SMenuExItem * pItem,BOOL bCheckFirstItem);
        void OnSubMenuHided(BOOL bUncheckItem);

        SMenuEx(SMenuExItem *pParent);
		void SendInitPopupMenu2Owner(int idx);
		SMenuExItem * m_pParent;
        SMenuExItem * m_pHoverItem;
        SMenuExItem * m_pCheckItem;

		BOOL	m_bMenuInitialized;
    };

}
