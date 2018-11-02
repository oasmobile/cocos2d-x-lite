/****************************************************************************
Copyright (c) 2010-2011 cocos2d-x.org

http://www.cocos2d-x.org

Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:

The above copyright notice and this permission notice shall be included in
all copies or substantial portions of the Software.

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
THE SOFTWARE.
 ****************************************************************************/
package org.cocos2dx.lib;

import android.content.Context;
import android.content.res.AssetManager;
import android.graphics.Bitmap;
import android.graphics.BitmapFactory;
import android.nfc.Tag;
import android.opengl.GLES20;
import android.opengl.GLSurfaceView;
import android.opengl.GLU;
import android.opengl.GLUtils;
import android.util.Log;

import java.io.BufferedInputStream;
import java.io.File;
import java.io.FileInputStream;
import java.io.IOException;
import java.io.InputStream;
import java.nio.ByteBuffer;
import java.nio.ByteOrder;
import java.nio.FloatBuffer;
import java.nio.ShortBuffer;

import javax.microedition.khronos.egl.EGLConfig;
import javax.microedition.khronos.opengles.GL10;
public class Cocos2dxRenderer implements GLSurfaceView.Renderer {
    // ===========================================================
    // Constants
    // ===========================================================

    private final static long NANOSECONDSPERSECOND = 1000000000L;
    private final static long NANOSECONDSPERMICROSECOND = 1000000;

    private static long sAnimationInterval = (long) (1.0 / 60 * Cocos2dxRenderer.NANOSECONDSPERSECOND);

    // ===========================================================
    // Fields
    // ===========================================================

    private long mLastTickInNanoSeconds;
    private int mScreenWidth;
    private int mScreenHeight;
    private boolean mNativeInitCompleted = false;

    // ===========================================================
    // Constructors
    // ===========================================================

    // ===========================================================
    // Getter & Setter
    // ===========================================================

    public static void setAnimationInterval(final float animationInterval) {
        Cocos2dxRenderer.sAnimationInterval = (long) (animationInterval * Cocos2dxRenderer.NANOSECONDSPERSECOND);
    }

    public void setScreenWidthAndHeight(final int surfaceWidth, final int surfaceHeight) {
        this.mScreenWidth = surfaceWidth;
        this.mScreenHeight = surfaceHeight;
    }

    // ===========================================================
    // Methods for/from SuperClass/Interfaces
    // ===========================================================
    public Context mContext = null;
    private int mFrameCount = 0;
    @Override
    public void onSurfaceCreated(final GL10 GL10, final EGLConfig EGLConfig) {
        Cocos2dxRenderer.nativeInit(this.mScreenWidth, this.mScreenHeight);
        this.mLastTickInNanoSeconds = System.nanoTime();
        mNativeInitCompleted = true;
        GLES20.glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

        GLES20.glEnable(GLES20.GL_TEXTURE_2D);
// Active the texture unit 0
        GLES20.glActiveTexture(GLES20.GL_TEXTURE0);

        initShader();
        int[] result = loadTexture(this);
        loadVertex(result[1], result[2]);
    }

    @Override
    public void onSurfaceChanged(final GL10 GL10, final int width, final int height) {
        Cocos2dxRenderer.nativeOnSurfaceChanged(width, height);
    }

    @Override
    public void onDrawFrame(final GL10 gl) {
        if (sAnimationInterval <= 1.0 / 60 * Cocos2dxRenderer.NANOSECONDSPERSECOND) {
            draw();
        }
        else {
            final long now = System.nanoTime();
            final long interval = now - this.mLastTickInNanoSeconds;

            if (interval < Cocos2dxRenderer.sAnimationInterval) {
                try {
                    Thread.sleep((Cocos2dxRenderer.sAnimationInterval - interval) / Cocos2dxRenderer.NANOSECONDSPERMICROSECOND);
                } catch (final Exception e) {
                }
            }
            /*
             * Render time MUST be counted in, or the FPS will slower than appointed.
            */
            this.mLastTickInNanoSeconds = System.nanoTime();
            draw();
        }
        /*
         * No need to use algorithm in default(60 FPS) situation,
         * since onDrawFrame() was called by system 60 times per second by default.
         */

    }

    public void drawHelloImage()
    {
        GLES20.glClear(GLES20.GL_COLOR_BUFFER_BIT);

        GLES20.glUseProgram(m_program);
        GLES20.glEnableVertexAttribArray(attribPosition);
        GLES20.glEnableVertexAttribArray(attribTexCoord);
        GLES20.glUniform1i(uniformTexture, 0);
        GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, mTexId);
        vertex.position(0);
        GLES20.glVertexAttribPointer(attribPosition, 3, GLES20.GL_FLOAT, false, 20, vertex);
        vertex.position(3);
        GLES20.glVertexAttribPointer(attribTexCoord, 2, GLES20.GL_FLOAT, false, 20, vertex);
        GLES20.glDrawElements(GLES20.GL_TRIANGLES, 6, GLES20.GL_UNSIGNED_SHORT, index);
    }

    public void draw()
    {
        if(mFrameCount == 3) {
            Cocos2dxRenderer.nativeInitScriptEngine();
            Cocos2dxRenderer.nativeRender();
//            drawHelloImage();
            mFrameCount++;
            return;
        }
        else if(mFrameCount < 3){
            drawHelloImage();
            mFrameCount++;
            return;
        }
//        Log.d("[pl]", "start native Render");
        if(mFrameCount < 10) {
            drawHelloImage();
            mFrameCount++;
        }
        Cocos2dxRenderer.nativeRender();
//        Log.d("[pl]", "finish native Render");
    }

    // ===========================================================
    // Methods
    // ===========================================================

    private static native void nativeTouchesBegin(final int id, final float x, final float y);
    private static native void nativeTouchesEnd(final int id, final float x, final float y);
    private static native void nativeTouchesMove(final int[] ids, final float[] xs, final float[] ys);
    private static native void nativeTouchesCancel(final int[] ids, final float[] xs, final float[] ys);
    private static native boolean nativeKeyEvent(final int keyCode,boolean isPressed);
    private static native void nativeRender();
    private static native void nativeInit(final int width, final int height);
    private static native void nativeOnSurfaceChanged(final int width, final int height);
    private static native void nativeOnPause();
    private static native void nativeOnResume();
    private static native void nativeOnLowMemory();
    private static native void nativeInitScriptEngine();

    public void handleActionDown(final int id, final float x, final float y) {
        Cocos2dxRenderer.nativeTouchesBegin(id, x, y);
    }

    public void handleActionUp(final int id, final float x, final float y) {
        Cocos2dxRenderer.nativeTouchesEnd(id, x, y);
    }

    public void handleActionCancel(final int[] ids, final float[] xs, final float[] ys) {
        Cocos2dxRenderer.nativeTouchesCancel(ids, xs, ys);
    }

    public void handleActionMove(final int[] ids, final float[] xs, final float[] ys) {
        Cocos2dxRenderer.nativeTouchesMove(ids, xs, ys);
    }

    public void handleKeyDown(final int keyCode) {
        Cocos2dxRenderer.nativeKeyEvent(keyCode, true);
    }

    public void handleKeyUp(final int keyCode) {
        Cocos2dxRenderer.nativeKeyEvent(keyCode, false);
    }

    public void handleOnPause() {
        /**
         * onPause may be invoked before onSurfaceCreated,
         * and engine will be initialized correctly after
         * onSurfaceCreated is invoked. Can not invoke any
         * native method before onSurfaceCreated is invoked
         */
        if (! mNativeInitCompleted)
            return;

        Cocos2dxHelper.onEnterBackground();
        Cocos2dxRenderer.nativeOnPause();
    }

    public void handleOnResume() {
        Cocos2dxHelper.onEnterForeground();
        Cocos2dxRenderer.nativeOnResume();
    }

    public void handleOnLowMemory() {

        Cocos2dxRenderer.nativeOnLowMemory();
    }

    private static native void nativeInsertText(final String text);
    private static native void nativeDeleteBackward();
    private static native String nativeGetContentText();

    public void handleInsertText(final String text) {
        Cocos2dxRenderer.nativeInsertText(text);
    }

    public void handleDeleteBackward() {
        Cocos2dxRenderer.nativeDeleteBackward();
    }

    public String getContentText() {
        return Cocos2dxRenderer.nativeGetContentText();
    }

    public static int loadShader(int type, String shaderCode){

        //创建一个vertex shader类型(GLES20.GL_VERTEX_SHADER)
        //或一个fragment shader类型(GLES20.GL_FRAGMENT_SHADER)
        int shader = GLES20.glCreateShader(type);

        // 将源码添加到shader并编译它
        GLES20.glShaderSource(shader, shaderCode);
        GLES20.glCompileShader(shader);

        return shader;
    }

    static int[] loadTexture(Cocos2dxRenderer renderer) {
        int[] textureId = new int[1];

// Generate a texture object
        GLES20.glGenTextures(1, textureId, 0);

        int[] result = null;

        if (textureId[0] != 0) {

            InputStream is = null;
            try {
                is = new BufferedInputStream(renderer.mContext.getAssets().open("res/raw-assets/resources/raw_image/start/AppStart.png"));
            }
            catch (IOException e) {

            }
            Bitmap bitmap;
            try {
                bitmap = BitmapFactory.decodeStream(is);
            } finally {
                try {
                    is.close();
                } catch (IOException e) {
                    throw new RuntimeException("Error loading Bitmap.");
                }
            }

            result = new int[3];
            result[0] = textureId[0]; // TEXTURE_ID
            result[1] = bitmap.getWidth(); // TEXTURE_WIDTH
            result[2] = bitmap.getHeight(); // TEXTURE_HEIGHT

// Bind to the texture in OpenGL
            GLES20.glBindTexture(GLES20.GL_TEXTURE_2D, textureId[0]);

// Set filtering
            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MIN_FILTER, GLES20.GL_LINEAR);
            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_MAG_FILTER, GLES20.GL_NEAREST);

            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_S, GLES20.GL_CLAMP_TO_EDGE);
            GLES20.glTexParameteri(GLES20.GL_TEXTURE_2D, GLES20.GL_TEXTURE_WRAP_T, GLES20.GL_CLAMP_TO_EDGE);

// Load the bitmap into the bound texture.
            GLUtils.texImage2D(GLES20.GL_TEXTURE_2D, 0, bitmap, 0);

// Recycle the bitmap, since its data has been loaded into OpenGL.
            bitmap.recycle();

            renderer.mTexId = textureId[0];
        } else {
            throw new RuntimeException("Error loading texture.");
        }

        return result;
    }

    private void initShader() {
        String vertexSource = "uniform mat4 u_MVPMatrix;\n" +
                "\n" +
                "attribute vec4 a_position;\n" +
                "attribute vec2 a_texCoord;\n" +
                "\n" +
                "varying vec2 v_texCoord;\n" +
                "\n" +
                "void main()\n" +
                "{\n" +
                "gl_Position = a_position;\n" +
                "v_texCoord = a_texCoord;\n" +
                "}";
        String fragmentSource = "precision lowp float;\n" +
                "\n" +
                "varying vec2 v_texCoord;\n" +
                "uniform sampler2D u_samplerTexture;\n" +
                "\n" +
                "void main()\n" +
                "{\n" +
                "gl_FragColor = texture2D(u_samplerTexture, v_texCoord);\n" +
                "}";

// Load the shaders and get a linked program
        m_program = Cocos2dxRenderer.loadProgram(vertexSource, fragmentSource);

// Get the attribute locations
        attribPosition = GLES20.glGetAttribLocation(m_program, "a_position");
        attribTexCoord = GLES20.glGetAttribLocation(m_program, "a_texCoord");

        uniformTexture = GLES20.glGetUniformLocation(m_program, "u_samplerTexture");

        GLES20.glUseProgram(m_program);
        GLES20.glEnableVertexAttribArray(attribPosition);
        GLES20.glEnableVertexAttribArray(attribTexCoord);
    }
    private int m_program = 0;
    private int attribPosition = 0;
    private int attribTexCoord = 0;
    private int uniformTexture = 0;
    private int mTexId = 0;

    public static int loadProgram(String vertexSource, String fragmentSource) {
// Load the vertex shaders
        int vertexShader = Cocos2dxRenderer.loadShader(GLES20.GL_VERTEX_SHADER, vertexSource);

// Load the fragment shaders
        int fragmentShader = Cocos2dxRenderer.loadShader(GLES20.GL_FRAGMENT_SHADER, fragmentSource);

// Create the program object
        int program = GLES20.glCreateProgram();

        if (program == 0) {
            throw new RuntimeException("Error create program.");
        }

        GLES20.glAttachShader(program, vertexShader);
        GLES20.glAttachShader(program, fragmentShader);

// Link the program
        GLES20.glLinkProgram(program);

        int[] linked = new int[1];

// Check the link status
        GLES20.glGetProgramiv(program, GLES20.GL_LINK_STATUS, linked, 0);

        if (linked[0] == 0) {
            GLES20.glDeleteProgram(program);
            throw new RuntimeException("Error linking program: " + GLES20.glGetProgramInfoLog(program));
        }

// Free up no longer needed shader resources
        GLES20.glDeleteShader(vertexShader);
        GLES20.glDeleteShader(fragmentShader);

        return program;
    }

    private void loadVertex(int width, int height) {

        float qw = 1.0f, qh = 1.0f;
        if(width * 1.0f / height < mScreenWidth * 1.0f / mScreenHeight)
        {
            qh = ((float)(mScreenWidth * height)) / (width * mScreenHeight);
        }
        else {
            qw = ((float)(width * mScreenHeight)) / (height * mScreenWidth);
        }
        float[] quadVertex = new float[] {
                -qw, qh, 0.0f,
                0, 0,
                -qw, -qh, 0.0f,
                0, 1.0f,
                qw, -qh, 0.0f,
                1.0f, 1.0f,
                qw, qh, 0.0f,
                1.0f, 0f,
        };
// float size = 4
        this.vertex = ByteBuffer.allocateDirect(quadVertex.length * 4)
                .order(ByteOrder.nativeOrder())
                .asFloatBuffer();

        this.vertex.put(quadVertex).position(0);

// short size = 2
        this.index = ByteBuffer.allocateDirect(quadIndex.length * 2)
                .order(ByteOrder.nativeOrder())
                .asShortBuffer();

        this.index.put(quadIndex).position(0);
    }

    private FloatBuffer vertex;
    private ShortBuffer index;

    private short[] quadIndex = new short[] {
            (short)(0), // Position 0
            (short)(1), // Position 1
            (short)(2), // Position 2

            (short)(2), // Position 2
            (short)(3), // Position 3
            (short)(0), // Position 0
    };
    // ===========================================================
    // Inner and Anonymous Classes
    // ===========================================================
}
