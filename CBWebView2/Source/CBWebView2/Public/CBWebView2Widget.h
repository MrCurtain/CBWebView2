#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "CBWebView2Widget.generated.h"
class SCBWebView2;



UCLASS()
class CBWEBVIEW2_API UCBWebView2Widget: public UWidget
{
	GENERATED_UCLASS_BODY()

	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnWebView2MessageReceived, FString, Message);
	DECLARE_DYNAMIC_DELEGATE_OneParam(FWebView2ScriptCallback, FString, Message);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadCompleted, bool, bSuccess);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnLoadStrat, FString, URL);
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnNewWindowRequested, FString, URL);
public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
	// 重写此函数以构造你的Slate界面
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	/**网页的默认链接地址*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="WebView2")
	FString URL;

	/**背景颜色，不可半透明，但可以背景透明*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearence")
	FColor BackgroundColor;

	/**是否显示网页链接栏*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearence")
	bool bShowAddressBar;

	/**是否显示控制栏*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Appearence")
	bool bShowControls;

	
public:
	UPROPERTY(BlueprintAssignable, Category = "WebView2|Event")
	FOnWebView2MessageReceived OnWebView2MessageReceived;

	UPROPERTY(BlueprintAssignable, Category = "WebView2|Event")
	FOnLoadCompleted OnWebView2LoadCompleted;

	UPROPERTY(BlueprintAssignable, Category = "WebView2|Event")
	FOnLoadStrat OnWebView2LoadStrat;

	UPROPERTY(BlueprintAssignable, Category = "WebView2|Event")
	FOnNewWindowRequested OnNewWindowRequested;
	
public:
	/**设置背景演示，若A=0，则表现为透明背景*/
	UFUNCTION(Blueprintable,BlueprintCallable,Category="Appearence")
	void SetBackgroundColor(FColor InBackgroundColor);

	/**执行前端脚本*/
	UFUNCTION(BlueprintCallable, Category="WebView2")
	void ExecuteScript(const FString& Script,FWebView2ScriptCallback Callback) const;

	/**加载网页*/
	UFUNCTION(BlueprintCallable, Category="WebView2")
	void LoadURL(const FString InURL) ;
	
	/**前进*/
	UFUNCTION(BlueprintCallable, Category="WebView2")
	void GoForward() const ;
	
	/**后退*/
	UFUNCTION(BlueprintCallable, Category="WebView2")
	void GoBack() const ;
	
	/**重新加载*/
	UFUNCTION(BlueprintCallable, Category="WebView2")
	void ReLoad() const ;
	
	/**停止加载*/
	UFUNCTION(BlueprintCallable, Category="WebView2")
	void Stop() const ;
	
protected:
	UFUNCTION()
	void OnWebView2MessageReceivedCallback(const FString& NewMessage);

	UFUNCTION()
	void OnWebView2LoadCompletedCallback(const bool& bSuccess);

	UFUNCTION()
	void OnWebView2NavigationStartingCallback(const FString& NewURL);

	UFUNCTION()
	void OnWebView2NewWindowRequestedCallback(const FString& NewURL);
private:
	TSharedPtr<SCBWebView2> CBWebView2;

	
};





