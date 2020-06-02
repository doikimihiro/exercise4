import cv2 
import csv
a = cv2.imread('/home/doi/naist/exercise4/ForwardProjector_exercise_No4_phantom_100x100.png', cv2.IMREAD_GRAYSCALE)
a = cv2.resize(a, (100, 100))
a = [[float(item) for item in row] for row in a]

for i in range (100):
    for j in range (100):
        a[i][j]=float(a[i][j])*20.0/255.0

with open("stock.csv", "w") as f:
    writer = csv.writer(f, lineterminator="\n")
    writer.writerows(a)

  
