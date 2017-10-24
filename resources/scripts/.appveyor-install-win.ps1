ls
git clone -q --depth=1 https://github.com/martinrotter/rssguard.wiki.git C:\rssguard-wiki
git config --global credential.helper store
Add-Content "$env:USERPROFILE\.git-credentials" "https://$($env:access_token):x-oauth-basic@github.com`n"
git config --global user.email "rotter.martinos@gmail.com"
git config --global user.name "martinrotter"
$file = (Get-ChildItem '*.7z').Name
echo "File to upload: $file"
$url = curl.exe --upload-file "$file" "https://transfer.sh/$file" --silent
echo "Obtained URL: $url"
echo " from powershell $url " >> C:\rssguard-wiki\Windows-development-builds.md
cd C:\rssguard-wiki
git add *.*
git commit -m "New files."
git pull origin master
git push origin master -v