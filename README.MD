# Windows Service C++ Template

このテンプレートは、Visual C++でWindowsサービスを作成するためのテンプレートです。

## Windowsサービスアプリケーションの概要

[Microsoftのドキュメント](https://docs.microsoft.com/ja-jp/dotnet/framework/windows-services/introduction-to-windows-service-applications)をちゃんと読んで下さい。サンプルはC#だけどWindowsサービスの何たるかまでは変わりません。

## 編集して使うファイル

### ConsoleMainProcess.cpp
Consoleセッションで実行した時の処理を書く。ただし、ビルドして生成される実行ファイルは、コマンドライン引数無しでは起動しませんので、リリースする際は、起動時に適当な文字列でもいいので、何かしらの引数が渡されるようにバッチファイルを作成する等をして下さい。

### ConsoleMainProcess.h
WinMainからのコマンドライン引数の型を変更することができます。変更方法はこのヘッダーにコメントで記載してあります。

### ServiceInformation.h
Windowsサービスをインストール、または実行する際に必要な情報が記述されています。ご自身が制作するWindowsサービスに合わせて変更して下さい。

### ServiceMainProcess.h
ServiceMainからのコマンドライン引数の型を変更することができます。変更方法はこのヘッダーにコメントで記載してあります。

#### Name
サービスの名前

#### DisplayName
サービスの表示名

#### Description
サービスの説明

#### StartType
サービスのスタートオプション。値は[ここ](https://docs.microsoft.com/en-us/windows/win32/api/winsvc/nf-winsvc-createservicea)のdwStartTypeで書かれている通りです。

#### DelayedStart
サービスを遅延開始にするかどうかのフラグ。ここをtrueにする場合、StartTypeはSERVICE_AUTO_STARTになります。

#### ExecutionUser
サービスを実行するユーザーアカウント。これをNULLにすると、LocalSystemアカウントになります。その他のユーザーの場合はソースコードのコメントを参照して下さい。

#### RequireAdministrator
サービスに管理者特権が必要かどうかのフラグです

## 使い方

ServiceProcess(ServiceMainProcess.h内に定義)クラスを継承するクラスを定義してService_MainProcessをoverrideして定義し、最後にGetServiceProcessInstance関数を定義し、最初に定義したクラスをポインター型で返して下さい。

## メイン関数について

本テンプレートを利用される方が定義するメイン関数は、Console_MainProcess関数とService_MainProcess関数の２つです。

### Console_MainProcess関数

Consoleセッションにおける処理を書くメイン関数です。

### Service_MainProcess関数

Windowsサービスとして実行する処理を書くメイン関数です。

### 予約済みコマンドライン引数

Console_MainProcess関数は、デフォルトではinstallとuninstallが予約済みとなっております。(変更可)

Service_MainProcess関数にはありません。

## ライセンス

このテンプレートは、MITライセンスで公開しております。

## 作者ホームページ/定義例

[トップページ](https://www.kamioda.tokyo/)

[ソースコード例](https://www.kamioda.tokyo/cpp/template/WindowsServiceCppTemplate) (制作中)

## その他注意事項

- このテンプレートを使ったとしても、Microsoftが決めたルールからは逃れられません
- このテンプレートでは、プロセスを占有するサービス(Win32 Own Process)のみ作ることができます
- Windowsサービスの開発以外で使わないで下さい。

## 作者がこれを使って開発した・しているもの

[WindowsServerResourceMonitor](https://github.com/AinoMegumi/WindowsServerResourceMonitor)
