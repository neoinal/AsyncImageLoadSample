AsyncImageLoadSample
====================

DXライブラリを使用して非同期に画像ファイルをロードするサンプル

DXライブラリの公式リファレンスにて、非同期にロードするための関数が用意されていました。
そのため、そちらを参考にしてください。

[ＤＸライブラリ置き場 リファレンスページ](http://homepage2.nifty.com/natupaji/DxLib/function/dxfunc_other.html#R21N1)

## 準備

DXライブラリの `プロジェクトに追加すべきファイル_VC用` に含まれるファイルをそれぞれ下記ディレクトリにコピーする。

- `*.h` ファイル → `$(ProjectDir)\Include`
- `*.lib` ファイル → `$(ProjectDir)\Lib`

画像ファイルを `$(ProjectDir)\img` ディレクトリに下記の名前で配置する。

- test1.jpg
- test2.jpg
- test3.jpg

## 終了方法

ウィンドウを閉じる。
