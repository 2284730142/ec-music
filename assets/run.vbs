Set ws = CreateObject("Wscript.Shell")
ws.currentdirectory = "assets"
ws.run "cmd /c NeteaseCloudMusicApi.exe",vbhide
