import pandas as pd

roll_dict = {}


symmetric = 0 # 1 if the graph is undirected
telemetry = 1


# read the csv file
# get the roll no. from the file name
with open('roll_no_to_id.csv', 'r') as f:
    lines = (f.readlines()[1:])

for line in lines:
    line = line.replace('\n', '').split(',')
    num = (line[1][2:])
    roll_dict[int(num)] = line[0]
    
def get_id_from_roll_no(roll_no):
    if(roll_no[0] == 'A'):
        if(int(roll_no[2:]) in roll_dict.keys()):
            return roll_dict[int(roll_no[2:])]
        else:
            if(telemetry): print("Not found id: ",roll_no)
            return -1
    else:
        if(int(roll_no) in roll_dict.keys()):        
            return roll_dict[int(roll_no)]
        else:
            if(telemetry): print("Not found id: ",roll_no)
            return -1
        

data = pd.read_csv('familiarity-google-form.csv')

data.drop(['Timestamp', 'Full Name','Link'], axis=1, inplace=True)

# drop the rows with empty values
data.dropna(inplace=True)

edges = set() # containing tuples of (id, id)

print(data.head())

for index, row in data.iterrows():
    for i in range(1, 5):
        for j in range(i+1, 5):
            left_edge = row[i]
            right_edge = row[j]
            if(type(left_edge)== type(None) or type(right_edge)== type(None)):
                continue
            left_edge = get_id_from_roll_no(row[i])
            right_edge = get_id_from_roll_no(row[j])
            
            if(left_edge == -1 or right_edge == -1):
                continue
            edges.add((left_edge, right_edge))
            if (symmetric): # if the graph is undirected
                edges.add((left_edge, right_edge))

# write the edges to a file
with open('familiarity-edges.csv', 'w') as f:
    f.write('Source,Target,Weight\n')
    for edge in edges:
        f.write(str(edge[0])+','+str(edge[1])+',1\n')


