# comp220-worksheetA

## Implemented Effect Prototypes
I have implemented prototypes of two of my chosen effects: Lighting and Collision Detection.

### Lighting
Currently, a Blinn-Phong lighting model has been implemented with ambient, diffuse and specular lighting parameters. This lighting is also compatible with textures. The lighting shaders also take into account the properties of an object's material, such as its specular power and colour.

### Collision Detection
BulletPhysics has been integrated to the project to provide the physics for the game. So far, although collision detection is working fine, only primative collision shapes (spheres and boxes) have been implemented. Because of this, the main landscape model does not currently have a collision mesh, as primative shapes would not be suitable for such a complex mesh.

## Profiling

## Plan
### Convex Hull Shape collision mesh
To create a suitably accurate collision shape for the complex landscape model, I will implement the btConvexHullShape which can create complex shapes from vertex data. This will require the vertex data of the model to be passed to it, so the Mesh class will have to be updated to store the vertex data.

### Shadows

## Resources
http://www.peroxide.dk/papers/collision/collision.pdf
https://learnopengl.com/Lighting/Basic-Lighting
http://www.opengl-tutorial.org/intermediate-tutorials/tutorial-16-shadow-mapping/
https://learnopengl.com/Advanced-Lighting/Shadows/Shadow-Mapping

