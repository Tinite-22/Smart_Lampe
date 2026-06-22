# Smart Lamp : Lampe Domotique Tactile Sans Contact

![Platform: Arduino](https://img.shields.io/badge/Platform-Arduino-00979D?style=for-the-badge&logo=arduino&logoColor=white)
![Language: C++](https://img.shields.io/badge/Language-C++-green?style=for-the-badge&logo=c%2B%2B)
![Focus: Domotique](https://img.shields.io/badge/Focus-Domotique%20%2F%20IoT-orange?style=for-the-badge)

Ce projet permet de fabriquer une **lampe intelligente qui fonctionne sans contact physique**. Grâce à un capteur infrarouge (IR), le système détecte le passage de la main pour basculer l'état de l'éclairage : **on passe la main une fois, la lampe s'allume ; on repasse la main, la lampe s'éteint.**
---

## Rôle des Composants

| Composant | Rôle dans le projet |
| :--- | :--- |
| **Arduino (Uno / Nano / Elegoo)** | Le cerveau du projet. Il lit le signal du capteur, exécute la logique algorithmique et commande le relais donc la lampe. |
| **Capteur Infrarouge (IR) d'obstacle** | Détecte la présence de la main. Il envoie un signal bas (`LOW`) lorsqu'un obstacle est détecté. |
| **Module Relais (1 Canal - Active-LOW)** | Interrupteur électronique. Il permet au circuit basse tension (5V de l'Arduino) de contrôler en toute sécurité le circuit haute tension (220V de la lampe). |
| **Lampe / Ampoule (220V)** | L'élément d'éclairage final qui sera branché sur le secteur de la maison. |

---

## Guide de Câblage (Connexions)

Le système est séparé en deux parties : la partie **Commande** (basse tension) et la partie **Puissance** (haute tension).

### 1. Circuit de Commande (Arduino 5V)
| Composant | Broche du Composant | Broche Arduino |
| :--- | :--- | :--- |
| **Capteur IR** | `VCC` | `5V` |
| **Capteur IR** | `GND` | `GND` |
| **Capteur IR** | `OUT` | `D2` |
| **Module Relais** | `VCC` | `5V` |
| **Module Relais** | `GND` | `GND` |
| **Module Relais** | `IN` | `D3` |

---

## ⚠️ N.B. : Connexion 220V & Consignes de Sécurité Impératives

Le raccordement d'un appareil fonctionnant sur le réseau électrique domestique (220V) présente des **risques mortels d'électrocution et d'incendie**. Lisez attentivement les instructions suivantes avant toute manipulation.

### Comment relier la lampe 220V au module relais ?
Le côté haute tension du relais possède généralement 3 borniers à vis : **COM** (Commun), **NO** (Normalement Ouvert / *Normally Open*), et **NC** (Normalement Fermé / *Normally Closed*).

Pour que la lampe soit éteinte par défaut au démarrage, suivez ce schéma de câblage :
1. Prenez le câble d'alimentation de votre lampe 220V.
2. Laissez le fil **Neutre (Bleu)** et le fil de **Terre (Vert/Jaune)** intacts et reliés directement à la douille de la lampe.
3. Sectionnez (coupez) uniquement le fil de **Phase (Marron ou Rouge)**.
4. Dénudez les deux extrémités du fil de Phase que vous venez de couper :
   - Connectez la première extrémité (qui vient de la prise murale) sur la borne **COM** du relais.
   - Connectez la deuxième extrémité (qui va vers la lampe) sur la borne **NO** du relais.

### Règles de Sécurité Fondamentales
* **HORS TENSION ABSOLUE :** Ne manipulez **JAMAIS** les fils électriques, ne dénudez rien et ne vissez rien tant que la prise 220V est branchée au mur. Débranchez physiquement la prise avant chaque modification.
* **ISOLATION DU RELAIS :** Le dessous du module relais possède des soudures à nu conductrices de 220V. Vous devez **impérativement** enfermer le module relais dans un boîtier isolant en plastique (boîte de dérivation ou boîtier imprimé en 3D). Aucun élément sous tension ne doit être accessible au toucher.
* **SÉPARATION DES CIRCUITS :** Veillez à ce que les fils fins en 5V reliés à l'Arduino ne croisent et ne touchent jamais les gros fils en 220V.
* **SERRAGE DES BORNES :** Assurez-vous que les fils de Phase sont solidement vissés dans les borniers du relais. Un fil mal serré peut créer un arc électrique, générer de la chaleur et provoquer un incendie.
* **NE PAS MANIPULER À NU :** Une fois le projet branché, ne touchez jamais l'Arduino, le capteur ou le relais avec vos mains nues ou humides.

---

## Installation & Utilisation

1. Installez l'**IDE Arduino** sur votre ordinateur.
2. Créez un nouveau croquis et collez-y le code disponible dans le dossier `Smart_lampe_code.ino` de ce dépôt.
3. Connectez votre carte Arduino en USB, sélectionnez le bon port COM et téléversez le programme.
4. Réalisez le câblage basse tension, puis le câblage haute tension en respectant scrupuleusement les consignes de sécurité ci-dessus.
5. Branchez la prise 220V. Passez votre main à environ 5-10 cm du capteur IR pour allumer ou éteindre la lampe !

---
