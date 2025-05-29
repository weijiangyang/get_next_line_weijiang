Objectif de get_next_line
Lire une ligne à la fois depuis un fd (file descriptor), sans perdre les données non encore utilisées (ce qu’on appelle ici le stash), et sans relire inutilement le fichier.
Organisation globale
  read_and_stash() → lit et concatène dans une "stash" jusqu’à fin de ligne ou EOF.
  extract_and_update() → extrait une ligne complète de la stash et met à jour cette dernière.
  get_next_line() → fonction principale appelée par l'utilisateur.
include "get_next_line.h"
  ici le header qui doit contenir :
  les déclarations (get_next_line, ft_strdup, ft_strjoin, etc.)
  la constante BUFFER_SIZE,
  les prototypes de fonctions utilitaires

Détail des fonctions
read_and_stash(int fd, char *stash, char *buffer)

But : lire le fichier jusqu’à ce qu’on ait trouvé une ligne complète (\n) ou la fin du fichier, et concaténer dans stash.

while (bytes_read > 0 && (!stash || !end_line(stash)))

➡️ Continue à lire tant qu'on n’a pas atteint la fin (read == 0) et qu’il n’y a pas encore de \n dans stash.

bytes_read = read(fd, buffer, BUFFER_SIZE);
buffer[bytes_read] = '\0';

➡️ On lit BUFFER_SIZE octets dans buffer, puis on le termine par \0 (utile pour strjoin, etc.).

if (!stash)
    stash = ft_strdup(buffer);
else {
    tmp = stash;
    stash = ft_strjoin(stash, buffer);
    free(tmp);
}

➡️ Si stash est vide, on le remplit directement. Sinon, on concatène l’ancien stash + buffer.

extract_and_update(char **stash)

But : extraire la ligne complète du stash, puis le mettre à jour pour garder ce qu’il reste (ou le vider).

line = extract_line(*stash);

➡️ Récupère une ligne (jusqu’à et y compris \n, ou jusqu’à fin de chaîne).

next = tmp + ft_strlen(line);
if (*next == '\0') *stash = NULL;
else *stash = ft_strdup(next);

➡️ On déplace le pointeur juste après la ligne extraite, pour ne garder que ce qu’il reste dans stash.

🔹 get_next_line(int fd)

But : fonction principale appelée par l’utilisateur, renvoie une ligne lue depuis fd.

static char *stash = NULL;

➡️ Le stash est statiquement stocké, donc il garde sa valeur entre plusieurs appels à get_next_line.

buffer = malloc(BUFFER_SIZE + 1);

➡️ On lit dans un buffer temporaire qu’on libère après la lecture.

stash = read_and_stash(fd, stash, buffer);

➡️ Mise à jour de stash avec les nouvelles données lues.

if (!stash || stash[0] == '\0') {
    free(stash);
    return NULL;
}

➡️ Rien à retourner (soit erreur, soit EOF).

line = extract_and_update(&stash);

➡️ On extrait une ligne, on met à jour le stash, et on la renvoie.

Cycle typique

   Appel get_next_line(fd)

   Lit jusqu’à trouver une ligne entière

   Stocke ce qui reste dans stash

   Renvoie la ligne

   Appel suivant recommence à partir du stash

 Fonctions utilitaires attendues

   ft_strdup → duplique une chaîne (strdup)

   ft_strjoin → concatène deux chaînes

   extract_line(char *) → extrait la ligne jusqu’à \n inclus

   end_line(char *) → renvoie vrai si un \n est présent   
