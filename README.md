# Baseconv  <img src="https://img.shields.io/badge/With%20Python%20Support-yellow?style=for-the-badge&logo=python" width="152"  height="" alt="Python-Support" style="margin-right:20px"  align="right"/>


# bcv — Base Converter CLI

**bcv** (*Base Converter*) est un outil en ligne de commande simple, rapide et libre, conçu pour convertir des nombres entre différentes bases numériques : **binaire**, **octale**, **décimale** et **hexadécimale**.

> Développé par **KerHack-Libre**, dans un esprit **éducatif et pratique**, pour aider chacun à acquérir une **base solide en numérisation informatique** — la fondation de tout système logiciel.

---

## Objectif du projet

Ce projet est né d’un besoin simple mais fondamental :
**comprendre, manipuler et visualiser les bases numériques** qui sont au cœur de tout ce que fait un ordinateur.

> Une chose aussi basique peut ouvrir des portes incroyables sur la compréhension du fonctionnement interne des machines — et même aider à créer de meilleurs logiciels.

**bcv** n’est pas qu’un convertisseur :
c’est un petit compagnon du quotidien pour les développeurs, étudiants, hackers, ou passionnés de bas niveau.
Je l’utilise moi-même chaque jour pour :
- inspecter et déboguer  des  signature sur des fichiers **fichiers binaires**
- ou simplement vérifier rapidement une conversion en **binaire / hex / octal** sans lancer d’outil lourd.

--- 

### Dimension éducative

Comprendre les bases numériques, c’est comprendre la langue native des ordinateurs.

**bcv** a été conçu dans un but éducatif: 

pour initier les étudiants et curieux aux bases du système de numérisation informatique ;

pour permettre aux développeurs de visualiser concrètement ce qui se cache derrière les chiffres et les octets ;

et pour montrer que même un petit outil simple peut être une porte d’entrée vers la programmation système et la conception logicielle.

## Fonctionnalités

- Conversion instantanée entre **bases 2, 8, 10 et 16**
- **Shell interactif** intégré (`b/`, `o/`, `x/` ou `exit`)
- **Détection automatique** du format d’entrée (`0b`, `0o`, `0x`)
- ⚙️ **Compact**, **rapide** et **sans dépendance**
- Parfait pour l’apprentissage, le scripting et le débogage
- Compatible **Unix/Linux**, compilable avec **Clang** ou **GCC**

---

## Installation

### 🔧 Depuis la source

```bash
git clone https://github.com/KerHack-Libre/baseconv.git
cd baseconv

meson setup build 
meson install -C build  




## Utilisation 
### ligne de commande 

```bash
bcv [OPTION] <NOMBRE> 

| Option         | Exemple     | Description              |
| :------------- | :---------- | :----------------------- |
| `-b <nombre>`  | `bcv -b 42` | Convertir en binaire     |
| `-o <nombre>`  | `bcv -o 42` | Convertir en octal       |
| `-x <nombre>`  | `bcv -x 42` | Convertir en hexadécimal |
| `-v`, `v`, `!` |             | Affiche la version       |
| `-h`, `h`, `?` |             | Affiche l’aide           |

``` 

### Mode Interactive 

Lancer simplement 
```bash 
bcv  
```
Puis entrer les commandes : 

```bash 
b/42       → convertit en binaire
x/255      → convertit en hexadécimal
o/77       → convertit en octal
exit       → quitte le shell
```

###  mode Rapide 

#### Exemples 

```bash 
$ bcv 12
DEC : 12
HEX : 0xC
OCT : 0o14
BIN : 0b1100

$ bcv 0xFEED
DEC : 65261
OCT : 0o177355
BIN : 0b1111111011101101

$ bcv E
DEC : 69
HEX : 0x45
OCT : 0o105
BIN : 0b1000101

```

Une Page de manuel est incluse 

```bash  
man ./docs/bcv.1
```
Elle décrit en détail les options, les exemples et le fonctionnement du shell interactif. 

## Exemple d’intégration Bash

```bash 
#!/bin/bash
# Exemple simple : conversion rapide dans un script
read -p "Entrer un nombre : " n
bcv $n
```

## Auteur

Umar Ba
jUmarB@protonmail.com

🌐 github.com/Jukoo

## ⚖️ Licence

Copyright (c) 2025
KerHack-Libre — Logiciel libre et distribué sans AUCUNE GARANTIE.

## À propos de KerHack-Libre

KerHack-Libre est une initiative qui vise à promouvoir des outils systèmes libres, légers et éducatifs,
inspirés de la philosophie Unix et du pragmatisme du libre.

« Faire simple, efficace et libre. » 

## Contribuer

Les contributions sont toujours les bienvenues !
Si tu veux participer :

* Ouvre une issue pour proposer une amélioration
* Soumets une pull request
* Ou simplement partage bcv avec d’autres passionnés du shell ! 
