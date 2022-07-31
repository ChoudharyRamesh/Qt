package com.qtadmob.ShareShot;

import com.google.android.gms.ads.MobileAds;
import com.google.android.gms.ads.initialization.InitializationStatus;
import com.google.android.gms.ads.initialization.OnInitializationCompleteListener;
import android.content.Context;
import com.google.android.gms.ads.AdRequest;
import com.google.android.gms.ads.AdSize;
import com.google.android.gms.ads.AdView;
import com.google.android.gms.ads.AdListener;
import com.google.android.gms.ads.InterstitialAd;
import com.google.android.gms.ads.LoadAdError;
import android.view.View;
import android.view.Window;
import android.view.ViewGroup;
import android.util.Log;
import android.graphics.Rect;
import android.widget.FrameLayout;
import android.view.ViewGroup.LayoutParams;
import android.app.Activity;
import java.lang.Runnable;
import android.os.Handler;
import android.os.Looper;
import android.view.ViewTreeObserver;
import java.lang.Exception;

//int rootWindowWidthInDp = (int) (rootWindowWidth / mContext.getResources().getDisplayMetrics().density);



public class QtAdMob
{
  static private String TAG = "QtAdMob";
  static private int statusBarHeight=0;
  static private int rootWindowHeight=0;
  static private int rootWindowWidth=0;
  static private ViewGroup viewGroup; // to hold Banner adView

  static private AdView bannerAdView;
  static private InterstitialAd mInterstitialAd;

  static private String BannerAdUnitId = "ca-app-pub-3940256099942544/6300978111";
  static private String InterstitialAdUnitId = "ca-app-pub-3940256099942544/1033173712";
  static private String TestDeviceId = "ca-app-pub-3940256099942544~3347511713";

  static private AdRequest adRequest;
  static private boolean isInterstitialAdIsLoading=false;

  static private Activity mActivity;
  static private Context mContext;

  static private Handler handler = new Handler(Looper.getMainLooper());

  static private long interval_BannerAd = 8000;// 8sec
  static private long interval_InterstitialAd = 30000; // 30sec
  static private long time_requestBannerAdAfterLaunch = 1000; // 1sec
  static private long time_requestInterstitialAdAfterLaunch = 8000; // 8sec

  static private boolean isActivityIsInBackGround = false;


  // static private long interval_BannerAd = 2*60000;// 2 min
  // static private long interval_InterstitialAd = 7*60000; // 7 min
  // static private long time_requestBannerAdAfterLaunch = 30000; // 0.5 min
  // static private long time_requestInterstitialAdAfterLaunch = 150000; // 2.5 min

  // call this function when app is loaded
 public static void initializeMobiledAdsSdk(final Context context,final Activity activity)
 {  mActivity = activity;
     mContext  = context;
     MobileAds.initialize(mContext, new OnInitializationCompleteListener()
     {
        @Override
        public void onInitializationComplete(InitializationStatus initializationStatus)
         {
             try{
             Rect rectangle = new Rect();
             Window window = mActivity.getWindow();
             window.getDecorView().getWindowVisibleDisplayFrame(rectangle);
             statusBarHeight = rectangle.top;
             View rootView = window.getDecorView().getRootView();
             viewGroup  = (ViewGroup) rootView;
             rootWindowWidth= rootView.getWidth();
             rootWindowHeight = rootView.getHeight();

             rootView.addOnLayoutChangeListener(new View.OnLayoutChangeListener()
             {
                 public void onLayoutChange( View v, int left, int top, int right,
                 int bottom, int oldLeft, int oldTop, int oldRight, int oldBottom)
                   {
                      rootWindowHeight=v.getHeight();
                      rootWindowWidth=v.getWidth();
                      setBannerAdAtBottom();
                   }
             });

            //prepare ad banners
             prepareBannerAd();
             prepareInterstitialAd();

             // prepare adRequest object
             adRequest = new AdRequest.Builder()
             .addTestDevice(TestDeviceId)
             .build();

              //request Ad
                 // request BannerAd
                 handler.postDelayed(new Runnable(){
                   @Override
                   public void run() {
                      requestBannerAd();
                   }
               },time_requestBannerAdAfterLaunch);

                // request InterstitialAd
                handler.postDelayed(new Runnable(){
                  @Override
                  public void run() {
                      requestInterstitialAd();
                  }
              },time_requestInterstitialAdAfterLaunch);

           }catch(Exception e){e.printStackTrace();}
        }
     });
 }

   private static void requestBannerAd()
    {
       try{
       if(bannerAdView==null){ Log.e(TAG,"AdView is null object "); return; }
       if(adRequest==null){ Log.e(TAG,"AdRequest is null object "); return; }
       bannerAdView.loadAd(adRequest);
       }catch(Exception e){e.printStackTrace();}
    }

  private static void requestInterstitialAd()
    {
        System.out.println("##### request Initiated");
        try{
              if(!isActivityIsInBackGround)
              {
                  if(!isInterstitialAdIsLoading)
                    {
                       isInterstitialAdIsLoading=true;
                       if(mInterstitialAd==null){ Log.e(TAG,"InterstitialAd is null object "); return; }
                       if(adRequest==null){ Log.e(TAG,"AdRequest is null object "); return; }
                        mInterstitialAd.loadAd(adRequest);
                   }
              }
          else
          { System.out.println("##### request Delayed bcz in background");
              handler.postDelayed(new Runnable(){
                @Override
                public void run() {
                    requestInterstitialAd();
                }
            },time_requestInterstitialAdAfterLaunch);
         }
      }catch(Exception e){e.printStackTrace();}
   }

  public static void hideBannerAd()
   {
       try{
      if(bannerAdView==null){ Log.e(TAG,"AdView is null object "); return; }
       bannerAdView.setVisibility(View.INVISIBLE);
       }catch(Exception e){e.printStackTrace();}
   }

  public static void showBannerAd()
   {
       try{
      if(bannerAdView==null){ Log.e(TAG,"AdView is null object "); return; }
       bannerAdView.setVisibility(View.VISIBLE);
       }catch(Exception e){e.printStackTrace();}
   }


 private static void prepareBannerAd()
 {
     //Banner Ad
     try{
     bannerAdView = new AdView(mActivity);
     bannerAdView.setAdSize(AdSize.BANNER);
     bannerAdView.setAdUnitId(BannerAdUnitId);
     FrameLayout.LayoutParams layoutParams = new FrameLayout.LayoutParams(FrameLayout.LayoutParams.WRAP_CONTENT,
                                                                        FrameLayout.LayoutParams.WRAP_CONTENT);
     bannerAdView.setLayoutParams(layoutParams);
     viewGroup.addView(bannerAdView);
     bannerAdView.setAdListener(new AdListener()
     {
          @Override
          public void onAdLoaded() {
              // Code to be executed when an ad finishes loading.
             bannerAdView.setVisibility(View.VISIBLE);
          }

          @Override
          public void onAdLeftApplication() {
              hideBannerAd();
                handler.postDelayed(new Runnable(){
                  @Override
                  public void run() {
                      showBannerAd();
                  }
                },interval_BannerAd);
            }

        @Override
        public void onAdFailedToLoad(LoadAdError adError) {
            // Code to be executed when an ad request fails.
            handler.postDelayed(new Runnable(){
              @Override
              public void run() {
                 requestBannerAd();
              }
          },time_requestBannerAdAfterLaunch/2);
        }

          @Override
          public void onAdClosed() {
              // Code to be executed when the interstitial ad is closed.
                 handler.postDelayed(new Runnable(){
                   @Override
                   public void run() {
                      requestBannerAd();
                   }
               },interval_BannerAd);
            }
       });
     }catch(Exception e){e.printStackTrace();}
  }

  private static void prepareInterstitialAd()
  {
      //InterstitialAd
      try{
      mInterstitialAd = new InterstitialAd(mContext);
      mInterstitialAd.setAdUnitId(InterstitialAdUnitId);
      mInterstitialAd.setAdListener(new AdListener()
      {
         @Override
           public void onAdLoaded() {
               // Code to be executed when an ad finishes loading.
             showInterstitialAd();
           }

           @Override
           public void onAdFailedToLoad(LoadAdError adError) {
               // Code to be executed when an ad request fails.
               isInterstitialAdIsLoading=false;
               handler.postDelayed(new Runnable(){
                 @Override
                 public void run() {
                     requestInterstitialAd();
                 }
               },time_requestInterstitialAdAfterLaunch/2);
           }

           @Override
           public void onAdClosed() {
               // Code to be executed when the interstitial ad is closed.
                  handler.postDelayed(new Runnable(){
                    @Override
                    public void run() {
                        requestInterstitialAd();
                    }
                  },interval_InterstitialAd);
             }
       });
     }catch(Exception e){e.printStackTrace();}
  }

  private static void showInterstitialAd()
  {
      System.out.println("##### request for show Initiated");
      if(!isActivityIsInBackGround)
      {
         mInterstitialAd.show();
         isInterstitialAdIsLoading=false;
      }
      else
      {
           System.out.println("##### request for show Delayed");
          handler.postDelayed(new Runnable(){
            @Override
            public void run() {
                showInterstitialAd();
            }
          },time_requestInterstitialAdAfterLaunch);
      }
  }

  private static void setBannerAdAtBottom()
    {
       try{
       if(bannerAdView==null){ Log.e(TAG,"AdView is null object "); return; }
        bannerAdView.setX((rootWindowWidth-bannerAdView.getWidth())/2);
        bannerAdView.setY((rootWindowHeight-bannerAdView.getHeight()));
         }catch(Exception e){e.printStackTrace();}
    }

  public static void setActivityVisibility(boolean visible)
   {
      if(visible)
      isActivityIsInBackGround=false;
      else  isActivityIsInBackGround=true;
    }
}
