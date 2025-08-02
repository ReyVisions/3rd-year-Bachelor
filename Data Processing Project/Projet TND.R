###Classification ascendente de hierarchisation (CAH)

#Ouverture du fichier et du jeu de donnees
haberman_data_directory <- normalizePath("C:/Users/remyx/OneDrive/Documents/Info L4/TND/Binome3/haberman.data");
haberman <- read.table(haberman_data_directory, sep=",",header=TRUE);
haberman

#Creation du dendrogramme
library(cluster)
cah=agnes(scale(haberman),method="ward")
plot(cah, xlab="Individus",ylab="Seuil",col.axis = "pink", col.lab = "pink",main="Dendrogramme haberman") 

#Decoupage du dendrogramme
classification=as.hclust(cah)
plot(rev(classification$height),type="h",xlab="Classes",ylab="Inertie",main="Dendrogramme coupe")

#Trace des classes sur le dendrogramme
plot(classification, labels = FALSE, main = "Partition en 4, 8 ou 32 classes", xlab = "", ylab = "", sub = "", axes = FALSE, hang = -1)
rect.hclust(classification, 4, border = "green3")
rect.hclust(classification, 8, border = "red3")
rect.hclust(classification, 32, border = "blue3")

#Creation de 4 clusters
classes=cutree(cah,k=4)
classes
haberman.classes=cbind.data.frame(haberman,as.factor(classes))
haberman.classes

#Ajout d'une 5eme variable classe
colnames(haberman.classes)[5]="Classe"

#Les 4 sous-tableaux des invididus regroupes par classe
haberman_classes_1 <- subset(haberman.classes, Classe == 1)
haberman_classes_2 <- subset(haberman.classes, Classe == 2)
haberman_classes_3 <- subset(haberman.classes, Classe == 3)
haberman_classes_4 <- subset(haberman.classes, Classe == 4)


#Utilisation des fonctions catdes et summary pour obtenir des statistiques sur les classes.
library("FactoMineR")
etude = catdes(haberman.classes, num.var=5, proba=0.05)
etude

summary(haberman_classes_1)
summary(haberman_classes_2)
summary(haberman_classes_3)
summary(haberman_classes_4)

#Tentative de trace de PCA 
res.pca = PCA(haberman.classes, quanti.sup = 1:3, quali.sup = 5,graph=T)

plot.PCA(res.pca,choix="ind",habillage=5)

#-----------------------------------------------------------------------#

###K means

#Calcul du nombre de clusters ideaux

set.seed(123) # Pour la reproductibilité des résultats
fviz_nbclust(scale(haberman), kmeans, method = "silhouette") +
  geom_vline(xintercept = 8, linetype = 2) # Ligne pour indiquer le maximum de silhouette


#Affichage des clusters
 classification_kmeans=kmeans(scale(haberman),centers=4)
fviz_cluster(classification_kmeans, data = scale(haberman), geom = "point", stand = FALSE, ellipse.type = "norm", ellipse.level = 0.95, repel = TRUE)

#Creation d'une 5eme variable asssociee a chaque individu
haberman.calcul=cbind.data.frame(haberman,factor(classification_kmeans$cluster))
haberman.calcul
colnames(haberman.calcul)[5]="Classe"

haberman_calcul_1 <- subset(haberman.calcul, Classe == 1)
haberman_calcul_2 <- subset(haberman.calcul, Classe == 2)
haberman_calcul_3 <- subset(haberman.calcul, Classe == 3)
haberman_calcul_4 <- subset(haberman.calcul, Classe == 4)

etude2 = catdes(haberman.calcul, num.var=5, proba=0.05)
etude2

summary(haberman_calcul_1)
summary(haberman_calcul_2)
summary(haberman_calcul_3)
summary(haberman_calcul_4)

resultat_kmeans=PCA(haberman.calcul,quanti.sup=1:3,quali.sup=5,graph=F)
plot(resultat_kmeans,choix="ind",habillage=5)

resultat=PCA(haberman.calcul,quanti.sup=1:3,quali.sup=5,graph=F)
res.hcpc=HCPC(resultat_kmeans,consol=TRUE)

cah_kmeans=agnes(scale(haberman),method="ward");
classif_kmeans=as.hclust(cah_kmeans);
plot(rev(classif_kmeans$height),type="h",ylab="hauteurs")