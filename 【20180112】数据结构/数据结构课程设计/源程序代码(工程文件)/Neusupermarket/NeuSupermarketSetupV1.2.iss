; 脚本由 Inno Setup 脚本向导 生成！
; 有关创建 Inno Setup 脚本文件的详细资料请查阅帮助文档！

#define MyAppName "NeuSupermarket"
#define MyAppVersion "1.2"
#define MyAppPublisher "QNeu"
#define MyAppURL "http://60.205.215.163/"
#define MyAppExeName "QNeuSupermarket.exe"

[Setup]
; 注: AppId的值为单独标识该应用程序。
; 不要为其他安装程序使用相同的AppId值。
; (生成新的GUID，点击 工具|在IDE中生成GUID。)
AppId={{C0F0D504-EBCD-433B-9263-5F519E737837}
AppName={#MyAppName}
AppVersion={#MyAppVersion}
;AppVerName={#MyAppName} {#MyAppVersion}
AppPublisher={#MyAppPublisher}
AppPublisherURL={#MyAppURL}
AppSupportURL={#MyAppURL}
AppUpdatesURL={#MyAppURL}
DefaultDirName={pf}\{#MyAppName}
DefaultGroupName={#MyAppName}
AllowNoIcons=yes
LicenseFile=D:\FangCloudV2\Qdoor\Programmers\Demo2\release\license.txt
InfoAfterFile=D:\FangCloudV2\Qdoor\Programmers\Demo2\release\help.txt
OutputDir=C:\Program Files\NeuSupermarket
OutputBaseFilename=NeuSupermarketSetup
SetupIconFile=D:\FangCloudV2\Qdoor\Programmers\Demo2\main.ico
Compression=lzma
SolidCompression=yes

[Languages]
Name: "basque"; MessagesFile: "compiler:Languages\Basque.isl"
Name: "brazilianportuguese"; MessagesFile: "compiler:Languages\BrazilianPortuguese.isl"
Name: "czech"; MessagesFile: "compiler:Languages\Czech.isl"
Name: "danish"; MessagesFile: "compiler:Languages\Danish.isl"
Name: "dutch"; MessagesFile: "compiler:Languages\Dutch.isl"
Name: "finnish"; MessagesFile: "compiler:Languages\Finnish.isl"
Name: "french"; MessagesFile: "compiler:Languages\French.isl"
Name: "german"; MessagesFile: "compiler:Languages\German.isl"
Name: "hebrew"; MessagesFile: "compiler:Languages\Hebrew.isl"
Name: "hungarian"; MessagesFile: "compiler:Languages\Hungarian.isl"
Name: "italian"; MessagesFile: "compiler:Languages\Italian.isl"
Name: "japanese"; MessagesFile: "compiler:Languages\Japanese.isl"
Name: "norwegian"; MessagesFile: "compiler:Languages\Norwegian.isl"
Name: "polish"; MessagesFile: "compiler:Languages\Polish.isl"
Name: "portuguese"; MessagesFile: "compiler:Languages\Portuguese.isl"
Name: "portuguesestd"; MessagesFile: "compiler:Languages\PortugueseStd.isl"
Name: "russian"; MessagesFile: "compiler:Languages\Russian.isl"
Name: "serbiancyrillic"; MessagesFile: "compiler:Languages\SerbianCyrillic.isl"
Name: "serbianlatin"; MessagesFile: "compiler:Languages\SerbianLatin.isl"
Name: "slovak"; MessagesFile: "compiler:Languages\Slovak.isl"
Name: "slovenian"; MessagesFile: "compiler:Languages\Slovenian.isl"
Name: "spanish"; MessagesFile: "compiler:Languages\Spanish.isl"
Name: "ukrainian"; MessagesFile: "compiler:Languages\Ukrainian.isl"

[Tasks]
Name: "desktopicon"; Description: "{cm:CreateDesktopIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked; OnlyBelowVersion: 0,6.1
Name: "quicklaunchicon"; Description: "{cm:CreateQuickLaunchIcon}"; GroupDescription: "{cm:AdditionalIcons}"; Flags: unchecked

[Files]
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\QNeuSupermarket.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\D3Dcompiler_47.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\Des3.exe"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\help.txt"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\icon_res.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\libEGL.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\libgcc_s_dw2-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\libGLESV2.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\libstdc++-6.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\libwinpthread-1.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\login.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\main.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\moc_login.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\moc_login.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\moc_predefs.h"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\moc_quiwidget.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\moc_quiwidget.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\moc_supermarket.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\moc_supermarket.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\opengl32sw.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_demo.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_demo.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_image.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_image.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_main.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_main.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_qss.cpp"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\qrc_qss.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\Qt5Core.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\Qt5Gui.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\Qt5Network.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\Qt5Svg.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\Qt5Widgets.dll"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\quiwidget.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\supermarket.o"; DestDir: "{app}"; Flags: ignoreversion
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\bearer\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\cache\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\iconengines\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\imageformats\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\platforms\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\translations\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
Source: "D:\FangCloudV2\Qdoor\Programmers\Demo2\release\user\*"; DestDir: "{app}"; Flags: ignoreversion recursesubdirs createallsubdirs
; 注意: 不要在任何共享系统文件上使用“Flags: ignoreversion”

[Icons]
Name: "{group}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"
Name: "{group}\{cm:ProgramOnTheWeb,{#MyAppName}}"; Filename: "{#MyAppURL}"
Name: "{group}\{cm:UninstallProgram,{#MyAppName}}"; Filename: "{uninstallexe}"
Name: "{commondesktop}\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: desktopicon
Name: "{userappdata}\Microsoft\Internet Explorer\Quick Launch\{#MyAppName}"; Filename: "{app}\{#MyAppExeName}"; Tasks: quicklaunchicon

[Run]
Filename: "{app}\{#MyAppExeName}"; Description: "{cm:LaunchProgram,{#StringChange(MyAppName, '&', '&&')}}"; Flags: nowait postinstall skipifsilent

