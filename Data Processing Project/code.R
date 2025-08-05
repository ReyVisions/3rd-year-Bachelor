
data <- read.csv("C:/Users/pc/Documents/L3/s6/TND/projet/Binome3/haberman.data",header = FALSE)
colnames(data) <- c("Age","Year of operation","NB positive axillary nodes","Survival Status")

summary(data)

pairs(data)
#date d'operation en fonction de l'age
plot(data[,1],data[,2],type="l",col="pink",lwd = 3,xlab="Patient's age",ylab="Operating year")

#Statut de survie en fonction du nombre de noeuds positifs
survival_meanPositiveNodes <- aggregate(data[,4] ~ data[,3], data, FUN=mean)
plot(survival_meanPositiveNodes[,1], survival_meanPositiveNodes[,2], type="l", col="pink",lwd = 3, xlab="NB positive axillary nodes", ylab="Mean survival status")

#Statut de survie en fonction de l'age
plot(data[,1],data[,4],type="l",col="pink",lwd = 3,xlab="Patient's age",ylab="Survival Status")

#Nombre de noeuds positifs en fonction de l'age
plot(data[,1],data[,3],type="p",col="pink",lwd = 3,xlab="Patient's age",ylab="NB positive axillary nodes")

#Statut de survie en fonction de l'annee d'operation
survival_meanOperatinfYear <- aggregate(data[,4] ~ data[,2], data, FUN=mean)
plot(survival_meanOperatinfYear[,1], survival_meanOperatinfYear[,2], type="l", col="pink",lwd = 3, xlab="Operating year", ylab="Mean survival status")

#------------------------boites a moustaches----------------------------
#Age
boxplot(data[,1])

#Annee d'operation
boxplot(data[,2])

#Nombre d'auxiliaires positifs
boxplot(data[,3])

#tout dans un seul graphique
boxplot(data[,-4])

boiteAMoustaches <- function(variable,nom){
  boxplot(variable, col="pink", xlab=nom, ylab="")
  
  # Calculer les quantiles
  quantiles <- quantile(variable)
  
  # Calculer la moyenne
  mean_survival <- mean(variable)
  
  # Obtenir les coordonnées y de la boîte à moustaches
  boxplot_stats <- boxplot(variable, plot=FALSE)
  box_y <- boxplot_stats$stats
  
  # Définir les positions verticales pour les annotations
  pos_quantiles <- c(quantiles[1], median(variable), quantiles[3])
  pos_mean <- mean_survival
  pos <- c(pos_quantiles, pos_mean)
  
  # Ajouter l'annotation pour la moyenne
  text(1, pos_mean, paste("Médiane:", quantiles[2]), pos=3)
  
  #Ajouter l'annotation pour le min
  text(1, quantiles[1], paste("Min:", min(variable)), pos=3)
  
  #Ajouter l'annotation pour le max
  text(1, quantiles[5], paste("Max:", max(variable)), pos=3)
}


boiteAMoustaches(data[,1],"Age")
















