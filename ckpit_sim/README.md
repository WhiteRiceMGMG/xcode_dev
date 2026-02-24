#I/F一覧(初期案)

公開I/F名　　　　　　　　　　　　　　　機能ラベル        
---
アクセル開度(%)                      : pwrtrn      
ブレーキ開度(%)                      : pwrtrn
クラッチ開度(%)                      : pwrtrn
ギアシフト情報(1-5,R,N)              : pwrtrn 
回転数(rpm)                          : pwrtrn
スピード(km/h)                       : pwrtrn
エンストフラグ(ビットフラグ)         : prtct
IG-ON許可フラグ(ビットフラグ)        : perm
ギアシフト許可フラグ(ビットフラグ)   : perm
オーバレブ状態フラグ(ビットフラグ)   : prtct
半クラ焼きつきフラグ(ビットフラグ)   : prtct
ブレーキ焼きつきフラグ(ビットフラグ) : prtct
IG-ON状態フラグ                      : perm


#ざっくり仕様
##全体の流れ
IG-ONしたらアクセル，ブレーキ，クラッチ開度を0%に．シフトはNにセット．
同時にIG-ON状態フラグを除く全ての状態を初期状態に戻す．




#コンポーネント(モジュール)ざっくり版
##Powertrain
駆動関係の演算

##Protection
保護ロジック

##Permission
動作許可ロジック

##Bridge
Cロジック提供ロジック




#MarkDownざっくり版
# 大見出し
## 中見出し
### 小見出し

## 箇条書き
- スロットル値
- ブレーキ値
- クラッチ値

**太文字**

## コードを書くとき
`g_sliderValue`
<pre> ```c double g_sliderValue; ``` </pre>
