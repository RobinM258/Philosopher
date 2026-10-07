# 🍝 Philosophers
---
## 📖 À propos

Le projet **Philosophers** consiste à simuler un groupe de philosophes assis autour d'une table ronde. Ils alternent entre trois états : **manger, dormir et penser**. 

Au milieu de la table se trouve un grand bol de spaghettis, mais il n'y a qu'un nombre limité de fourchettes. Pour manger, un philosophe doit obligatoirement utiliser deux fourchettes (une dans sa main gauche, une dans sa main droite). L'objectif principal est de gérer la synchronisation des threads pour éviter les **deadlocks** (interblocages) et faire en sorte qu'aucun philosophe ne meure de faim (starvation).

---

## ⚙️ Fonctionnalités & Choix techniques

*   🧵 **Threads et Mutexes (Partie obligatoire) :** Chaque philosophe est représenté par un thread distinct, et chaque fourchette est protégée par un `mutex` pour éviter les accès concurrents non contrôlés.
*   ⏱️ **Gestion précise du temps :** Utilisation de fonctions temporelles (comme `gettimeofday`) pour suivre l'exacte chronologie des actions et détecter si un philosophe dépasse son `time_to_die`.
*   📢 **Affichage sécurisé :** Les messages d'état de chaque philosophe sont protégés par un mutex d'écriture pour éviter que les lignes ne se mélangent dans la sortie standard.

---

## 🚀 Compilation & Utilisation

Clone le dépôt, compile le projet avec le `Makefile` fourni, puis exécute le programme en lui passant les arguments requis :

```bash
git clone https://github.com/RobinM258/Philosopher.git
cd Philosopher
make
./philosophers "number_of_philosophers" "time_to_die" "time_to_eat"
"time_to_sleep"
