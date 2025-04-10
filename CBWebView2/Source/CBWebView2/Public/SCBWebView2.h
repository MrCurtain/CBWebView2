﻿#pragma once
#include "CoreMinimal.h"
#include "WebView2Window.h"

class SConstraintCanvas;
DECLARE_DELEGATE_OneParam(FWebView2ScriptCallbackNative, const FString& /*Data*/)

class CBWEBVIEW2_API SCBWebView2:public SCompoundWidget
{
public:
	SLATE_BEGIN_ARGS(SCBWebView2)
		: _URL(TEXT("https://cn.bing.com/?mkt=zh-CN"))
		,_Color(FColor(255,255,255,255))
		, _ShowAddressBar(false)
		, _ShowControls(false)
		,_ShowInitialThrobber(false)
		
	{
		
	}
		
		SLATE_ARGUMENT(FString,URL)
		
		SLATE_ARGUMENT(FColor,Color)
		/** Whether to show an address bar. */
		SLATE_ARGUMENT(bool, ShowAddressBar)

		/** Whether to show standard controls like Back, Forward, Reload etc. */
		SLATE_ARGUMENT(bool, ShowControls)

		/** Whether to show a throbber overlay during browser initialization. */
		SLATE_ARGUMENT(bool, ShowInitialThrobber)
		
		
		SLATE_EVENT(FOnWebView2MessageReceivedNactive,NewOnWebView2MessageReceived)
		SLATE_EVENT(FOnNavigationCompletedNactive,NewOnWebView2NavigationCompleted)
		SLATE_EVENT(FOnNavigationStartingNactive,NewOnNavigationStarting)
		SLATE_EVENT(FOnNewWindowRequestedNactive,NewOnNewWindowRequestedNactive)
		SLATE_EVENT(FOnCursorChangedNactive,NewOnCursorChangedNactive)
	SLATE_END_ARGS()
	
	SCBWebView2();
    ~SCBWebView2();
public:
	void Construct( const FArguments& InArgs,TSharedRef<SWindow> InParentWindowPtr);

	virtual FReply OnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void OnMouseLeave(const FPointerEvent& MouseEvent) override;
	virtual bool HasKeyboardFocus() const override;
	virtual void Tick(const FGeometry& AllottedGeometry, const double InCurrentTime, const float InDeltaTime) override;
	virtual int32 OnPaint( const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect, FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle, bool bParentEnabled ) const override;
	virtual FVector2D ComputeDesiredSize(float) const override;
	virtual FCursorReply OnCursorQuery(const FGeometry& MyGeometry, const FPointerEvent& CursorEvent) const override;

	 void BeginDestroy();
	 void ExecuteScript(const FString& Script,FWebView2ScriptCallbackNative ScriptCallback=FWebView2ScriptCallbackNative()) const;

public:
	/**加载网页*/ 
	void LoadURL(const FString InURL) ;
	/**前进*/
	void GoForward() const ;
	/**后退*/
	void GoBack() const ;

	/** 如果浏览器可以向后导航则返回 true。 */
	bool CanGoBack() const;

	/** 如果浏览器可以向前导航，则返回 true。 */
	bool CanGoForward() const;
	/**重新加载*/
	void ReLoad() const ;
	/**停止加载*/
	void Stop() const ;

	/** document当前是否正在加载。 */
	bool IsLoading() const;

	/** 停止加载 */
	void StopLoad();

	/** 重新加载页面 */
	void Reload();

	/**获取当前网页标题. */
	FText GetTitleText() const;

	/**
	* 获取地址栏中显示的 URL，这可能不是框架中当前加载的 URL。
	*
	* @return 地址栏 URL。
	*/
	FText GetAddressBarUrlText() const;
private:
	/** Navigate backwards. */
	FReply OnBackClicked();

	/** Navigate forwards. */
	FReply OnForwardClicked();

	/** Get text for reload button depending on status */
	FText GetReloadButtonText() const;

	/** Reload or stop loading */
	FReply OnReloadClicked();

	/** Invoked whenever text is committed in the address bar. */
	void OnUrlTextCommitted( const FText& NewText, ETextCommit::Type CommitType );

	/** Get whether loading throbber should be visible */
	EVisibility GetLoadingThrobberVisibility() const;
	
public:
	FOnWebView2MessageReceivedNactive OnWebView2MessageReceived;
	FOnNavigationCompletedNactive OnWebView2NavigationCompleted;
	FOnNavigationStartingNactive OnWebView2NavigationStarting;
	FOnNewWindowRequestedNactive OnWebView2NewWindowRequested;
	FOnCursorChangedNactive OnebView2CursorChangedNactive;

	
	/** The initial throbber setting */
	bool bShowInitialThrobber;
	/**是否显示地址栏*/
	bool bShowAddressBar;
	/**是否线上控制栏*/
	bool bShowControls;

	
public:
	void SetBackgroundColor(FColor InBackgroundColor);
private:
	TSharedPtr<FWebView2Window> WebView2Window;

	/** Editable text widget used for an address bar */
	TSharedPtr< SEditableTextBox > InputText;
	
	FString InitializeURL;
	FColor BackgroundColor;
	FGuid UniqueId;

	HWND WebViewWindowHandle;

	FReply Handle;

	bool bCanGoBack =false;
	bool bCanGoForward =false;
	FString Title;
	FString  URL;

	//缩放比
  mutable  float FixSacale;
private:
	TSharedPtr<SConstraintCanvas> Canvas;// 绝对布局容器

	TArray<TSharedPtr<SImage>> Images;
	TSharedPtr<SOverlay> PositionOverlay; //
};
