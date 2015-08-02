class Button
{


  Button()
  {
    el=false;
    pressed=false;
    p_pressed=false;
    col=color(0, 0, 255);
    loc=12.5;
  }
  void click(int pos)
  {
    if (mouseX<=width/2+25&&mouseY<= pos*height/5+25 &&mousePressed&& width/2-25<=mouseX &&  pos*height/5-25<=mouseY)
    {
      if (!pressed)
        el=!el;
      pressed=true;
    }
    else
    {
      p_pressed=pressed;
      pressed=false;
    }
    if (el==true&&pressed==false&&p_pressed==true)
    {
      col=color(0, 0, 255);
      loc=12.5;
    }
    else if (pressed==false&&p_pressed==true)
    {
      loc=-12.5;
      col=color(0, 255, 0);
    } 
    fill(col);
    rect(width/2, pos*height/5+loc, 50, 25);
  }


  boolean el, pressed, p_pressed;
  float loc;
  color col;
}
