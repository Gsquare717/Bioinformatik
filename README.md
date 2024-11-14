Bioinformatik I - Übung 1
=========================

Dieses Codegerüst soll Ihnen als Grundlage für das Erstellen einer generischen Sequenzklasse
dienen. Die Idee hinter dieser Klasse ist, eine einzige Implementierung der Sequenzlogik
zu schreiben, die eigentlichen Buchstaben der Sequenz jedoch austauschbar zu machen.

Bauen des Codegerüsts
---------------------
*Diese Anleitung bezieht sich auf das Bauen auf den CIP Rechnern der Bioinformatik*

Bevor Sie das Codegerüst ohne Fehler bauen können, benötigen Sie eine Leerimplementierung aller Klassen,
d.h. Sie müssen alle fehlenden cpp-Dateien ergänzen. Sehen Sie sich dazu CMakeLists.txt an.

Das Codegerüst verwendet das CMake Buildsystem, welches es vereinfacht C++ Code
zu kompilieren. Sie können das Codegerüst wie folgt erstellen:

 1. Legen Sie im Ordner in der sich diese README.md befindet einen Ordner `build` an:
```
mkdir build
```

 2. Wechseln sie in den neu erstellten Ordner hinein:
```
cd build
```

 3. Rufen Sie dann CMake auf:
```
cmake ..
```

 4. Nun können Sie den Code mittels make erstellen:
```
make -j 8
```
 Die Zahl hinter `-j` gibt die Anzahl an Prozessorkernen an, die
 zum Erstellen des Codes verwendet werden sollen.
 Ihre Ausführbare Datei liegt nun direkt im `build` Ordner.

### Bauen auf eigenen Systemen
 * Überlegen Sie sich ob sie nicht per SSH arbeiten möchten.
   Via:
```
ssh username@bioXX.studcs.uni-sb.de
```
   können Sie sich auf den CIP Rechnern einloggen. (Hierbei `XX` durch eine
   Zahl zwischen 01-22 und `username` durch Ihren Benutzernamen ersetzen.)
   Unter Windows müssen Sie dazu einen SSH Client wie z.B.
   [Putty](http://www.chiark.greenend.org.uk/~sgtatham/putty/download.html) installieren.
 * Falls Sie eine funktionierende Entwicklungsumgebung besitzen, müssen Sie eventuell
   den Pfad zu ihrer Google Test Bibliothek (gtest) in der CMakeLists.txt anpassen.


Ausführung Ihrer Anwendung
--------------------------
Um Ihre Anwendung auszuführen, müssen Sie diese wie oben
beschrieben gebaut haben. Danach können Sie die Anwendung vom
`build` Ordner aus mittels:
```
./name_of_program [parameter]
```
ausführen.

Ausführung der Unittests
------------------------
Um Ihre Unittests auszuführen, tippen Sie:
```
make test
```
Einzelne Tests (z.B. für Sequence) können vom `build` Ordner aus Sie mittels:
```
./test/Sequence_test
```
ausführen.

Hinzufügen eigenen Codes
------------------------
Um eigene Dateien zu ihrem Projekt hinzuzufügen, müssen Sie die CMakeLists.txt Dateien
bearbeiten. In der CMakeLists.txt im Verzeichnis dieser README.md können Sie Dateien zum
`add_library` Aufruf hinzufügen.

Ihre Unittests können Sie am Ende der Datei `CMakeLists.txt` hinzufügen.
Unittests müssen unter Zurhilfenahme der Google Test Bibliothek geschrieben werden.
Die Dokumentation hierzu finden sie [hier](https://code.google.com/p/googletest/wiki/V1_7_Primer).

Implementierung
---------------
Dies wird wie folgt erreicht:

```
template<typename Alphabet>
class Sequence {
	// Klassendefinition hier
};

class DNA {
public:
	// Zulässige Buchstaben
	enum class Characters { A, G, T, C };

	// Methoden zur Konvertierung
	static char toChar(Characters c);
	static Characters toChar(char c);
};

class RNA {
public:
	// Zulässige Buchstaben
	enum class Characters { A, G, U, C };

	// Methoden zur Konvertierung
	static char toChar(Characters c);
	static Characters toChar(char c);
};

// Wir können nun eine DNA Sequenz durch
// Einsetzen des richtigen Templateparameters erzeugen:
Sequence<DNA> sequence = Sequence<DNA>::fromString("AGTC");
```

Beachten Sie, das weder DNA noch RNA in irgendeiner Weise von
einer gemeinsamen Basisklasse erben. Sie implementieren jedoch
Funktionen mit identischer Signatur (toChar, toCharacter) und definieren einen Typen
mit dem selben Namen (Characters). Template Programmierung verlässt
sich daher darauf, dass die Parameter eine vom Programmierer bestimmte
Konvention einhalten. Ist dies nicht erfüllt, schlägt die Kompilation
mit mehr oder weniger aussagekräftigen Fehlermeldungen fehl.

###Beachten Sie Folgendes:

 * Schreiben Sie Ihren Code auch im Hinblick auch mögliche, falsche Eingaben.
   Hierfür ist bereits die Exception `InvalidCharacter` vordefiniert.
 * Template Code *muss* in einer Headerdatei implementiert werden. Implementieren
   Sie Templates nur dann in .cpp Dateien, wenn Sie genau wissen was Sie tun.
 * Für die Implementierung dieses Codes ist *kein einziger* Aufruf von new/delete
   nötig. Ebenso benötigen Sie keine Smart Pointer.

