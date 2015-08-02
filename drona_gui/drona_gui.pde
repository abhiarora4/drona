//import processing.serial.*; //import the Serial library
PFont font;

PImage angel;
int ypos;
int xpos;
float opa;
color col;//stores three integer values
int inc;
int mouseX_p;
int mouseY_p;
int locX, locY;
int locXh, locYh;
int locX2, locY2;
int locX2h, locY2h;
int textbox=0;
boolean textclick=false;
String text[];
float literals[];
int y;


//Serial myPort;  // Create object from Serial class
String val; 



Button click1, click2, click3, click4;


void setup()
{
  angel=loadImage("angel.jpg");
  //col=color(100, 200, 255);
  font=loadFont("AgencyFB-Bold-48.vlw");
  size(255*2, 255*2);
  smooth();
  textSize(60);
  ypos=70;
  frameRate(120000);

  locX=width/8 ;
  locY= height/2;

  locX2=7*width/8 ;
  locY2= height/2;

  click1 = new Button();
  click2 = new Button();
  click3 = new Button();
  click4 = new Button();
  text= new String[5];
  text[0]=" ";
  text[1]=" ";
  text[2]=" ";
  text[3]=" ";
  text[4]=" ";

  literals=new float[5];

  //String portName = Serial.list()[0]; //change the 0 to a 1 or 2 etc. to match your port
 // myPort = new Serial(this, portName, 9600);
}
void pointer()
{

  if (mouseX<width-10 && mouseY<height-10 && mouseX>1 && mouseY >1)
    fill(255, 0, 0);
  else
    noFill();
  rect(mouseX, mouseY, 10, 10);
}

void draw()
{

  angel.resize(width, height);
  rectMode(CENTER);
  background(angel);
 
  fill(0, 255, 0);
  textAlign(BASELINE);
  textSize(60);
  text("COPTER", width/4, 50);
  stroke(122, 211, 10);
  strokeWeight(5);
  line(width/4, 60, 360, 60);
  noStroke();

  fill(123);

  ellipse(width/8, height/2, 100, 100);
  ellipse(7*width/8, height/2, 100, 100);
  if ((width/8)-mouseX<50&&mouseX-(width/8)<50&&(height/2)-mouseY<50&&mouseY-(height/2)<50&&mousePressed)
  {
    locX=width/8;
    locY=mouseY;
  }
  fill(0, 255, 0);
  rect(locX, locY, 20, 20);


  if ((7*width/8)-mouseX<50&&mouseX-(7*width/8)<50&&(height/2)-mouseY<50&&mouseY-(height/2)<50&&mousePressed)
  {
    locX2=7*width/8;
    locY2=mouseY;
  }
  else
  {
    locX2=7*width/8 ;
    locY2= height/2;
  }
  rect(locX2, locY2, 20, 20);
  if ((width/8)-mouseX<50&&mouseX-(width/8)<50&&(height/2)-mouseY<50&&mouseY-(height/2)<50&&mousePressed)
  {
    locXh=mouseX;
    locYh=height/2;
  }
  else
  {
    locXh=width/8 ;
    locYh= height/2;
  }
  stroke(255, 0, 0);
  noFill();
  rect(locXh, locYh, 20, 20);

  if ((7*width/8)-mouseX<50&&mouseX-(7*width/8)<50&&(height/2)-mouseY<50&&mouseY-(height/2)<50&&mousePressed)
  {
    locX2h=mouseX;
    locY2h=height/2;
  }
  else
  {
    locX2h=7*width/8 ;
    locY2h= height/2;
  }

  rect(locX2h, locY2h, 20, 20);

  noStroke();
  fill(123);


  rect(width/2, height/5, 50, 50);
  rect(width/2, 2*height/5, 50, 50);
  rect(width/2, 3*height/5, 50, 50);
  rect(width/2, 4*height/5, 50, 50);

  click1.click(1);
  click2.click(2);
  click3.click(3);
  click4.click(4);

  fill(150);

  rect(width/8, 3*height/4+50, 50, 25);
  rect(width/8, 3*height/4, 50, 25);
  rect(width/8, 3*height/4-50, 50, 25);
  rect(width/8, 3*height/4+100, 50, 25);

  rect(7*width/8, 3*height/4+50, 50, 25);
  rect(7*width/8, 3*height/4, 50, 25);
  rect(7*width/8, 3*height/4-50, 50, 25);
  rect(7*width/8, 3*height/4+100, 50, 25);
  if (mouseX<width/8+25&&mouseX>width/8-25&&mouseY>3*height/4-12.5-50&&mouseY<3*height/4+12.5-50&&mousePressed)
  {
    textbox=1;
    textclick=true;
  }

  if (mouseX<width/8+25&&mouseX>width/8-25&&mouseY>3*height/4-12.5&&mouseY<3*height/4+12.5&&mousePressed)
  {
    textbox=2;
    textclick=true;
  }
  
  if (mouseX<width/8+25&&mouseX>width/8-25&&mouseY>3*height/4-12.5+50&&mouseY<3*height/4+12.5+50&&mousePressed)
  {
    textbox=3;
    textclick=true;
  }

  if (mouseX<width/8+25&&mouseX>width/8-25&&mouseY>3*height/4-12.5+100&&mouseY<3*height/4+12.5+100&&mousePressed)
  {
    textbox=4;
    textclick=true;
  }

  if (mousePressed&&textclick==false)
  {
    textbox=0;
  }
  textclick=false;

  textAlign(CENTER, CENTER);
  textSize(10);
  fill(0);

  text("Kp", width/8, 3*height/4-70);
  text("Ki", width/8, 3*height/4-25);
  text("Kd", width/8, 3*height/4+25);
  textAlign(LEFT, CENTER);

  switch(textbox)
  {
  case 1:
    text(text[textbox]+(frameCount/10 % 2 == 0 ? "_" : ""), width/8-20, 3*height/4-50);
    text(text[2], width/8-20, 3*height/4);
    text(text[3], width/8-20, 3*height/4+50);
    text(text[4], width/8-20, 3*height/4+100);
    break;
  case 2:
    text(text[textbox]+(frameCount/10 % 2 == 0 ? "_" : ""), width/8-20, 3*height/4);
    text(text[1], width/8-20, 3*height/4-50);
    text(text[3], width/8-20, 3*height/4+50);
    text(text[4], width/8-20, 3*height/4+100);
    break;
  case 3:
    text(text[textbox]+(frameCount/10 % 2 == 0 ? "_" : ""), width/8-20, 3*height/4+50);
    text(text[2], width/8-20, 3*height/4);
    text(text[1], width/8-20, 3*height/4-50);
    text(text[4], width/8-20, 3*height/4+100);
    break;
  case 4:
    text(text[textbox]+(frameCount/10 % 2 == 0 ? "_" : ""), width/8-20, 3*height/4+100);
    text(text[2], width/8-20, 3*height/4);
    text(text[3], width/8-20, 3*height/4+50);
    text(text[1], width/8-20, 3*height/4-50);
    break;
  default:
    text(text[2], width/8-20, 3*height/4);
    text(text[3], width/8-20, 3*height/4+50);
    text(text[1], width/8-20, 3*height/4-50);
    text(text[4], width/8-20, 3*height/4+100);
  }

  println(literals[textbox] + " length " + text[textbox].length());
  pointer();
  
}

void keyPressed()
{
  if (key!=CODED&&(key=='1'||key=='2'||key=='3'||key=='4'||key=='5'||key=='6'||key=='7'||key=='8'||key=='9'||key=='0'||key=='.'))
  {
    if (textbox!=0)
    {
      if (text[textbox].length()<6)
      {
        text[textbox]+=str( key);
        if (Float.isNaN(float(text[textbox]))) 
        {
          text[textbox] = text[textbox].substring(0, Math.max(0, text[textbox].length()-1));
        }
        if (Float.isNaN(float(text[textbox]) ))
        {
          text[textbox]+='0';
          text[textbox]+='.';
        }
        literals[textbox]=float(text[textbox]);
      }
    }
  }
  else if (key==CODED)
  {
    if (keyCode == LEFT) 
    {
      text[textbox] = text[textbox].substring(0, Math.max(0, text[textbox].length()-1));
      literals[textbox]=float(text[textbox]);
    }

    if (Float.isNaN(literals[textbox])) 
    {
      literals[textbox]=0.00;
    }
  }

  if (key == ENTER&&textbox!=0&&textbox<4) 
  {
    textbox=textbox+1;
  }
}
