import pickle 
filehandler = open("./tx.pkl", 'r') 
object = pickle.load(filehandler)
print object
