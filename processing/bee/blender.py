import bpy
import math


def create_mesh_obj(verts, edges, faces, name="mesh"):
    mesh_data = bpy.data.meshes.new(name + "_data")
    mesh_data.from_pydata(verts, edges, faces)
    mesh_obj = bpy.data.objects.new(name, mesh_data)
    bpy.context.collection.objects.link(mesh_obj)
    return mesh_obj


# get xy values from csv file
file = open('points.csv', 'r')
lines = file.readlines()
for line in lines:
    coords = line.split(',')
    x.append(coords[0].strip())
    y.append(coords[1].strip())

#num_rings = 13
verts = [(x[i], 0, y[i]) for i in range(len(x))]
edges = []
faces = []

obj = create_mesh_obj(verts, edges, faces, name="ellipse")
#obj.rotation_euler = (0, math.radians(90), 0)
