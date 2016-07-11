library(rpart)
library(partykit)

train <- read.csv("train.csv")

fit <- rpart(Borrower ~ Home + Marital + Annual, data=train, control=rpart.control(minsplit=1, minbucket=1,minsurrogate=4,cp=0.01))

plot(as.party(fit))

