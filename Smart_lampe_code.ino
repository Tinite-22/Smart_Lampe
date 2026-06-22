// --- 1. DÉCLARATION DES BROCHES ---
const int brocheCapteur = 2;  // Définit la broche D2 pour lire le capteur IR (const = ne pourra pas être modifiée par erreur)
const int brocheRelais = 3;   // Définit la broche D3 pour piloter le relais 

// --- 2. VARIABLES D'ÉTAT (La mémoire du programme) ---
bool etatLampe = false;       // Stocke l'état virtuel de la lampe : "false" = éteinte / "true" = allumée
int etatCapteurActuel;        // Va stocker la lecture instantanée du capteur (HIGH ou LOW) à chaque tour de boucle
int etatCapteurPrecedent = HIGH; // Mémorise l'état du tour précédent (Initialisé à HIGH car un capteur IR au repos émet un signal HIGH)


void setup() {
  // --- 3. CONFIGURATION MATÉRIELLE (Exécutée une seule fois au démarrage) ---
  
  pinMode(brocheCapteur, INPUT);  // Met la broche 2 en mode "Écoute" (reçoit le signal du capteur)
  pinMode(brocheRelais, OUTPUT);  // Met la broche 3 en mode "Action" (envoie du courant au relais)

  // SÉCURITÉ : Sur un relais "Active-LOW", le repos (éteint) correspond à 5V (HIGH). 
  // On applique immédiatement HIGH pour éviter que la lampe ne flashe un quart de seconde à l'allumage de l'Arduino.
  digitalWrite(brocheRelais, HIGH); 
  
  Serial.begin(9600); // Ouvre le canal de communication avec le PC (vitesse : 9600 bits/seconde) pour le Moniteur Série
}


void loop() {
  // --- 4. BOUCLE PRINCIPALE (Tourne à l'infini, des milliers de fois par seconde) ---

  // On lit les valeurs envoyées par le capteur IR (S'il voit un obstacle = LOW, sinon = HIGH)
  etatCapteurActuel = digitalRead(brocheCapteur);

  // On ne déclenche l'action QUE si le capteur voit un obstacle (LOW) ET qu'au tour précédent il n'en voyait pas (HIGH).
  // Cela évite que la lampe ne clignote en boucle si on laisse la main immobile devant le capteur.
  if (etatCapteurActuel == LOW && etatCapteurPrecedent == HIGH) {
    
    // On inverse la valeur de la mémoire : si c'était true ça devient false, et inversement.
    etatLampe = !etatLampe; 

    // On applique physiquement ce que la mémoire vient de décider :
    if (etatLampe == true) {
      
      // Relais Active-LOW : on lui envoie 0V (LOW) pour fermer le circuit 220V et allumer l'ampoule
      digitalWrite(brocheRelais, LOW); 
      Serial.println("Lampe : ALLUMÉE");

    } else {
      
      // Relais Active-LOW : on lui envoie 5V (HIGH) pour rouvrir le circuit 220V et couper l'ampoule
      digitalWrite(brocheRelais, HIGH);  
      Serial.println("Lampe : ÉTEINTE");

    }

    // "Filtre anti-rebond" : on fige le microcontrôleur 0.3 seconde. 
    // Sans ça, les micro-variations électriques au moment où ta main passe déclencheraient le "if" 4 fois de suite.
    delay(300); 
  }

  // Étape cruciale pour le tour suivant : le "présent" d'aujourd'hui devient le "passé" de demain.
  etatCapteurPrecedent = etatCapteurActuel;
}
