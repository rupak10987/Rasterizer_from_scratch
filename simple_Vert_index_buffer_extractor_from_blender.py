import bpy

obj = bpy.data.objects['Cube']
mesh = obj.data

normals = []
indices = []
mats = []
#manually put materials and cols of material here
col0=[255,0,0]
col1=[0,255,0]
col2=[0,0,255]
for face in mesh.polygons:
    indices.append(face.vertices[0])
    indices.append(face.vertices[1])
    indices.append(face.vertices[2])
    if face.material_index==0:
        mats.append(col0[0])
        mats.append(col0[1])
        mats.append(col0[2])
    elif face.material_index==1:
        mats.append(col1[0])
        mats.append(col1[1])
        mats.append(col1[2])
    elif face.material_index==2:
        mats.append(col2[0])
        mats.append(col2[1])
        mats.append(col2[2])
    
    for i in range(len(face.vertices)):
        v = mesh.vertices[face.vertices[i]]
        normals.append([v.normal[0],v.normal[1],v.normal[2]])

verts = []
for vert in mesh.vertices:
    verts.append(vert.co.x)
    verts.append(vert.co.y)
    verts.append(vert.co.z)

uvs = []
for uv_layer in mesh.uv_layers:
    for x in range(len(uv_layer.data)):
        uvs.append(uv_layer.data[x].uv)
out_cpp_str="Number_of_verticies "+str(len(verts)/3)+"\n"
out_cpp_str+="Number_of_Faces "+str(len(indices)/3)+"\n"       
out_cpp_str+="Vertex Buffer: \n"
for i in range(len(verts)):
    out_cpp_str+=str(verts[i])+','
    if (i+1)%3==0:
        out_cpp_str+="\n"
  

out_cpp_str+="\nIndex Buffer: \n"
for i in range(len(indices)):
    out_cpp_str+=str(indices[i])+','
    if (i+1)%3==0:
        out_cpp_str+="\n"

out_cpp_str+="\nCol_Buffer: \n"
for i in range(len(mats)):
    out_cpp_str+=str(mats[i])+','
    if (i+1)%3==0:
        out_cpp_str+="\n"
            
cpp_filepath = bpy.path.abspath("//")+"new_bal"+".txt"



f = open(cpp_filepath, 'w+')
f.write(out_cpp_str)
f.close()


