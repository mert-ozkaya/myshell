-İşletim Sistemleri Dersi Proje Ödevi-


B161210029 Mert ÖZKAYA
B161210026 Semih DEMİRCİ
B161210035 Alperen ÇİNKAYA


KOMUTLAR:

komut	: '<tekli komutlar>'
örnek	: ls -a
	- tekli komutlar direkt olarak çalıştırılabilir.
	 (Herhangi bir komut yazılabilir)


komut	: cat < 'FileName.txt'
örnek	: cat < test
	- 'cat' komutu ile giriş yönlendirme
	 (Bir dosyayı dup2 sinyali ile giriş olarak ayarlayabilir)


komut	: cat 'File1Name.txt' > 'File2Name.txt'
örnek	: cat score > out
	- 'cat' komutu ile giriş ve çıkış yönlendirme
	 (Bir dosyayı giriş diğer dosyayı ise çıkış olarak ayarlayarak dosyadan dosyaya direkt olarak yazdırabilir)


komut	: 'komut' &
örnek	: sleep &
	- '&' komutu ile process'i arka planda çalıştırma
	 (& işareti ile bir komutu sigaction sistem çağrısı ile arka planda çalıştırabilir)

