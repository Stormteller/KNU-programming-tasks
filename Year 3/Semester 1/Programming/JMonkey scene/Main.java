package mygame;

import com.jme3.app.SimpleApplication;
import com.jme3.material.Material;
import com.jme3.math.ColorRGBA;
import com.jme3.math.Vector3f;
import com.jme3.renderer.RenderManager;
import com.jme3.scene.Geometry;
import com.jme3.scene.Node;
import com.jme3.scene.shape.Box;
import com.jme3.scene.shape.Cylinder;
import com.jme3.math.FastMath;
import com.jme3.input.KeyInput;
import com.jme3.input.controls.KeyTrigger;
import com.jme3.input.controls.AnalogListener;
import com.jme3.input.controls.ActionListener;
import com.jme3.light.DirectionalLight;
import com.jme3.texture.Texture;
import com.jme3.terrain.geomipmap.TerrainQuad;
import com.jme3.texture.Texture.WrapMode;



class mainPlane {
    public float angle = 0;
    public Geometry geom;
    public final float HEIGHT = 10.0f;
    public final float WIDTH = 5.0f;
    public final float THICKNESS = 0.1f;
    
    public mainPlane() {
        Box plane = new Box(HEIGHT, WIDTH, THICKNESS);
        geom = new Geometry("Box", plane);
        geom.rotate((float)Math.toRadians(90.0f), 0.0f, 0.0f);
    }
    
    public mainPlane(float startAngle) {
        angle = startAngle;
        Box plane = new Box(10.0f, 5.0f, 0.1f);
        geom = new Geometry("Box", plane);
        geom.rotate((float)Math.toRadians(90.0f), 0.0f, 0.0f);
        geom.rotate(0.0f, (float)Math.toRadians(angle), 0.0f);
        geom.setLocalTranslation(0.0f, HEIGHT * (float)Math.sin(Math.toRadians(angle)) , 0.0f);
    }
    
    public void rotateTo(float a) {    
        if (angle + a <= 90 && angle + a >= 0) {
            angle += a;
            geom.setLocalTranslation(0.0f, HEIGHT * (float)Math.sin(Math.toRadians(angle)) , 0.0f);
            geom.rotate(0.0f, (float)Math.toRadians(a), 0.0f);
        }
    }
    
    public void rotateWithCylinder(float a, mainCylinder cylinder) {    
        if (angle + a <= 90 && angle + a >= 0) {
            angle += a;
            geom.setLocalTranslation(0.0f, HEIGHT * (float)Math.sin(Math.toRadians(angle)) , 0.0f);
            geom.rotate(0.0f, (float)Math.toRadians(a), 0.0f);
            
            cylinder.setPosition(
                    (HEIGHT) * (float)Math.cos(Math.toRadians(angle)) - cylinder.RADIUS - THICKNESS,
                    (2*HEIGHT - cylinder.RADIUS + THICKNESS) * (float)Math.sin(Math.toRadians(angle)) + cylinder.RADIUS,
                    0.0f);
        }
    }
}


class mainCylinder {
    public final float RADIUS;
    public float x = 0;
    public float y = 0;
    public float z = 0;
    public float velocityX = 0;
    public float velocityY = 0;
    public float velocityZ = 0;
    public Geometry geom;
    
    public mainCylinder(float height, float radius) {
        RADIUS = radius;
        Cylinder cylinder = new Cylinder(36, 72, radius, height, true);
        geom = new Geometry("Cylinder", cylinder);
        geom.setLocalTranslation(0.0f, radius, 0.0f);
    }
    
    public mainCylinder(float height, float radius, mainPlane plane) {
        RADIUS = radius;
        Cylinder cylinder = new Cylinder(36, 72, radius, height, true);
        geom = new Geometry("Cylinder", cylinder);
        x = (plane.HEIGHT) * (float)Math.cos(Math.toRadians(plane.angle)) - RADIUS - plane.THICKNESS;
        y = (2*plane.HEIGHT - RADIUS + plane.THICKNESS) * (float)Math.sin(Math.toRadians(plane.angle)) + RADIUS;
        geom.setLocalTranslation(x, y, 0.0f);
    }
    
    public void moveTo(float x, float y, float z) {
        this.x += x;
        this.y += y;
        this.z += z;
        geom.move(x, y, z);
    }
    
    public void setPosition(float x, float y, float z) {
        this.x = x;
        this.y = y;
        this.z = z;
        geom.setLocalTranslation(x, y, z);
    }
}

/**
 * test
 * @author normenhansen
 */
public class Main extends SimpleApplication {
    private TerrainQuad terrain;
    Material matTerrain;
    private mainPlane plane;
    private mainCylinder cylinder;
    private float gravity = 0.2f;
    private float frictionWood = 0.01f;
    private float frictionSand = 0.05f;
    private boolean isRunning = false;
    
    public static void main(String[] args) {
        Main app = new Main();
        app.start();
    }
    
    @Override
    public void simpleInitApp() {
        flyCam.setMoveSpeed(50);
        //Plane
        plane = new mainPlane(60.0f);
        Material planeMat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        //planeMat.setColor("Color", ColorRGBA.Gray);
        
        Texture wood2 = assetManager.loadTexture(
            "Textures/myWood2.jpg");
        planeMat.setTexture("ColorMap", wood2);
        plane.geom.setMaterial(planeMat);
        
        Node planeNode = new Node("planeNode");
        planeNode.attachChild(plane.geom);
        
        //Cyliner
        cylinder = new mainCylinder(5.0f, 1.0f, plane);
        Material cylMat = new Material(assetManager, "Common/MatDefs/Misc/Unshaded.j3md");
        //cylMat.setColor("Color", ColorRGBA.Green);
        Texture wood1 = assetManager.loadTexture(
            "Textures/myWood1.jpg");
        cylMat.setTexture("ColorMap", wood1);
        cylinder.geom.setMaterial(cylMat);
        
        Node cylNode = new Node("cylNode");
        cylNode.attachChild(cylinder.geom);
        
        //Terrain
        matTerrain = new Material(assetManager, 
            "Common/MatDefs/Terrain/Terrain.j3md");
        
        Texture sand1 = assetManager.loadTexture(
            "Textures/mySand1.jpg");
        sand1.setWrap(WrapMode.Repeat);
        matTerrain.setTexture("Tex1", sand1);
        matTerrain.setFloat("Tex1Scale", 64f);
       
        float[] hmap = new float[512];
        terrain = new TerrainQuad("mainTerrain", 65, 513, hmap);
        terrain.setMaterial(matTerrain);
        
        //Light
        DirectionalLight sun = new DirectionalLight();
        sun.setDirection(new Vector3f(1,0,-2).normalizeLocal());
        sun.setColor(ColorRGBA.White);
        
        rootNode.attachChild(terrain);
        rootNode.addLight(sun);
        rootNode.attachChild(cylNode);
        rootNode.attachChild(planeNode);
        initKeys();
    }
    
    private void initKeys() {
        inputManager.addMapping("Lift_up", new KeyTrigger(KeyInput.KEY_X));
        inputManager.addMapping("Lift_down", new KeyTrigger(KeyInput.KEY_C));
        inputManager.addMapping("Start_moving", new KeyTrigger(KeyInput.KEY_SPACE));
        inputManager.addListener(liftingListener, "Lift_up", "Lift_down", "Start_moving");
    };

    private ActionListener liftingListener = new ActionListener() {
        public void onAction(String name, boolean keyPressed, float tpf) {
            if(!isRunning) {
                if(name.equals("Lift_up") && keyPressed) {
                    plane.rotateWithCylinder(5.0f, cylinder);
                }
                if(name.equals("Lift_down") && keyPressed) {
                    plane.rotateWithCylinder(-5.0f, cylinder);
                }
            }
            if(name.equals("Start_moving") && keyPressed) {
                if(!isRunning) {
                    reinitScene();
                }
                isRunning = !isRunning;                
            }
        }
    };
    
    public void reinitScene(){
        cylinder.velocityX = 0;
        cylinder.velocityY = 0;
        cylinder.velocityZ = 0;
        plane.rotateWithCylinder(0.0f, cylinder);
    }
    
    @Override
    public void simpleUpdate(float tpf) {
        if(isRunning) {
            if(cylinder.y > cylinder.RADIUS) {
                cylinder.moveTo(-cylinder.velocityX, -cylinder.velocityY, 0.0f);
                float alpha = (float)Math.toRadians(plane.angle);
                float accel = gravity * ((float)Math.sin(alpha) - frictionWood * (float)Math.cos(alpha)); 
                cylinder.velocityX += accel * (float)Math.cos(alpha); 
                cylinder.velocityY += accel * (float)Math.sin(alpha);
                float cylVelocity = cylinder.velocityX * (float)Math.cos(alpha) + cylinder.velocityY * (float)Math.sin(alpha);
                cylinder.geom.rotate(0.0f, 0.0f, cylVelocity / cylinder.RADIUS);
                if(cylinder.y < cylinder.RADIUS) {
                    Vector3f currPos = cylinder.geom.getLocalTranslation();
                    cylinder.setPosition(currPos.x, cylinder.RADIUS, currPos.z);
                    cylinder.velocityY = 0;                    
                }
            } else {
                if(cylinder.velocityX > 0) {
                    cylinder.moveTo(-cylinder.velocityX, 0.0f, 0.0f);
                    float accel = -gravity * frictionSand; 
                    cylinder.velocityX += accel;
                    float cylVelocity = cylinder.velocityX;
                    cylinder.geom.rotate(0.0f, 0.0f, cylVelocity / cylinder.RADIUS);
                } else {
                    isRunning = false;
                }
            }
            try {
            Thread.sleep(50);
            } catch(InterruptedException e) {}            
        }
    }

    @Override
    public void simpleRender(RenderManager rm) {
        //TODO: add render code
    }
}
