# Requirement specification

## 1. Introduktion

### 1.1 Produkts omfång

Produkten ska kunna mäta och visa upp olika värden för att kunna ge krukväxter de bästa möjliga förutsättningarna att växa på rätt sätt. Med denna produkt ska man kunna se ifall man behöver vattna sin växt så att man kan lättare hantera de växter man har hemma.

### 1.2 Målgrupp

Denna produkt är avsedd för dem som har en växt hemma och inte vet hur, vill ha koll på eller inte orkar ha koll på hur en krukväxt ska skötas.

### 1.3 Avsedd användning

Denna produkt är avsedd att placeras i en krukväxts kruka. Den ska sedan automatiskt mäta av och visa upp olika värden som jordens fuktighet. 

### 1.4 Definitioner och Förkortningar

- UV: Ultraviolett
- LED: Light Emitting Diode
- LCD: Liquid Crystal Display 
  
### 1.5 Innehållsförteckning

- [Requirement specification](#requirement-specification)
  - [1. Introduktion](#1-introduktion)
    - [1.1 Produkts omfång](#11-produkts-omfång)
    - [1.2 Målgrupp](#12-målgrupp)
    - [1.3 Avsedd användning](#13-avsedd-användning)
    - [1.4 Definitioner och Förkortningar](#14-definitioner-och-förkortningar)
    - [1.5 Innehållsförteckning](#15-innehållsförteckning)
  - [2. Systemkrav](#2-systemkrav)
    - [2.1 Funktionella krav](#21-funktionella-krav)
    - [2.2 Icke-funktionella krav](#22-icke-funktionella-krav)
    - [2.3 Krav på hårdvara](#23-krav-på-hårdvara)
  - [3. Krav på externt gränssnitt](#3-krav-på-externt-gränssnitt)
    - [3.1 Användargränssnitt](#31-användargränssnitt)
    - [3.2 Hårdvarugränssnitt](#32-hårdvarugränssnitt)
    - [3.3 Mjukvarugränssnitt](#33-mjukvarugränssnitt)


## 2. Systemkrav 

### 2.1 Funktionella krav

**Jordfuktighetssensor:**

- Om växten behöver vattnas ska en röd LED lysa.
- Om växten snart behöver vattnas ska en gul LED lysa.
- Om växten inte behöver vattnas ska en grön LED lysa.
- Om växten har fått för mycket vatten ska en blå LED lysa.

**Ljussensor:**

- Om växten får för mycket ljus lyser en unik gul LED.
- Om växten får för lite ljus ska samma led lysa.
- Ljussensorn ska ha marginal för att ljuset inte kommer att vara optimalt.

**LCD:**

- LCD ska kunna visa information för bevattning
- LCD ska kunna visa information om ljusförhållanden.
- LCD ska kunna visa om det är för mycket ljus.
- LCD ska kunna visa om det är för lite ljus.
- LCD tänds i 10 sekunder när användaren påbörjar en interaktion med någon av knapparna (1, 2, 3).
- En knapp (1) ska växla vilken information man ser på LCD
- En knapp (2) ska höja gränsen för acceptabelt värde på det mätvärde man ser på LCD
- En knapp (3) ska sänka gränsen för acceptabelt värde på det mätvärde man ser på LCD

**Tid:**

- När värdet justeras ska det nya gränsvärdet för den sensorn visas på LCD under 5 sekunder.
- Efter värdet har justerats och LCD visat det nya värdet ska den vara på ytterligare 10 sekunder och visa sensordata.
  
- Nya mätvärden ska registreras var 5:e minut.
- Användaren ska kunna välja att nya värden mäts kontinuerligt genom att hålla ned knapp 1 i 3 sekunder. 

### 2.2 Icke-funktionella krav

- Produkten ska vara lättanvänd.
- Som användare ska man förstå hur man ska sätta ner produkten i en kruka.

### 2.3 Krav på hårdvara

- Det ska finnas en jordfuktighetssensor
- Det ska finnas en UV-ljussensor
- Arduino UNO R4 WIFI

## 3. Krav på externt gränssnitt

### 3.1 Användargränssnitt

Det ska finnas tre knappar och 5 LED. En grön (1), två gula (2, 5), en röd (3) och en blå (4). Det ska även finnas en LCD som ska visa information utefter vad användaren valt att visa. Ifall den gröna LED lyser behöver inte växten vattnas, ifall den blå LED lyser har man vattnat för mycket. Om gul LED (2) lyser betyder det att växten snart behöver vattnas. Lyser den röda LED bör växten vattnas snarast möjligt. Om LED 5 (gul) lyser betyder det att växten får för mycket ljus i det fönster den står nu.

**Knapp 1:** Denna knapp växlar mellan vilken data LCD visar. Varje knapptryck stegar igenom alla sensorer som finns och skärmen hålls igång 10 sekunder efter att användaren inte har gjort någon input.

**Knapp 2:** Denna knapp ökar det godtagbara värdet för sensorn som användaren har valt med knapp 1. Om skärmen har slocknat utgår denna knapp från att användaren vill ändra hur fuktig jorden får vara innan man måste vattna igen.

**Knapp 3:** Denna knapp minskar det godtagbara värdet för sensorn som användaren har valt med knapp 1. Om skärmen har slocknat utgår denna knapp från att användaren vill ändra hur fuktig jorden får vara innan man måste vattna igen.

### 3.2 Hårdvarugränssnitt

Arduinon ska läsa av jordfuktighetssensorn och UV-sensorn på analoga pins.

### 3.3 Mjukvarugränssnitt

Programmet ska använda sig av Arduino IDE och de bibliotek som finns tillgängliga där. 
