
let howmany=100;
let random_in;
let start=false;
let  user_inp;

const vertices=[];
const hull=[];
let left;
let curr_vertex;  //along the hull
let check_point=0;  //check the points
let next_check_point=-1;
let nextVertex; 
let inp_num;
let num_button;

function setup (){
  createCanvas(700,600);
  background(color('#F5F5F5'));
  frameRate(60);

  let reset_button=createButton("RESET");
  reset_button.position(width-reset_button.width, height+1);
  reset_button.mousePressed(do_reset);
  
  user_inp=createInput("Random: true or false");
  user_inp.position(0,height+3);
  
  button=createButton("Let's Start!");
  button.position(user_inp.x+user_inp.width, height+4);
  button.mousePressed(fixvalue);
  
  let pause_it=createButton("PAUSE");
  pause_it.position(reset_button.x-pause_it.width-1, reset_button.y);
  pause_it.mousePressed(do_pause);
  
  let play_it=createButton("PLAY");
  play_it.position(pause_it.x-play_it.width-1, reset_button.y);
  play_it.mousePressed(do_play);

  let step_it=createButton("STEP");
  step_it.position(play_it.x-step_it.width-1, play_it.y);
  step_it.mousePressed(do_step);
  // 
  
}

function do_reset(){
  location.reload();
}

function do_pause(){
  noLoop();
}

function do_play(){
  loop();
}

function do_step(){
  noLoop();
  redraw(1);
}

function fixvalue(){
  const txt_inp= user_inp.value();
  console.log(txt_inp);
  if( txt_inp=='true') {
    inp_num=createInput('How many vertices?', [int]);
    inp_num.position(user_inp.x, user_inp.y+user_inp.height+2);

    num_button=createButton("OKAY");
    num_button.position(user_inp.x+user_inp.width+1, user_inp.y+user_inp.height+2.5);
    num_button.mousePressed(do_howmany);
    
  }
  else if(txt_inp=='false')random_in=false;

  //go_now.position=(inp_num.x+inp_num.width+1, inp_num.y);
  user_inp.value('');
}

function do_howmany(){
  let mage=int(inp_num.value());
  howmany=mage;
  random_in=true;
    if(random_in==true){
      for(let i=0; i<howmany; i++){
        vertices.push(createVector(random(10, width-20), random(10,height-20)));
      }
      vertices.sort((a,b) =>a.x-b.x);
      left=vertices[0];
      curr_vertex=left;
      hull.push(curr_vertex);
      nextVertex=vertices[1]; //guess
      check_point=2;
    }
  return;
}

function keyPressed(){
  if(keyCode==RETURN && !start) init();
}
let cont=false;
function mousePressed(){
  stroke(color('#ADA8B6')); strokeWeight(8);
  if(random_in==false && !start){
    if(mouseY<height-10){point(mouseX, mouseY);
    vertices.push(createVector(mouseX, mouseY));
    }
  }
}

function init(){
  vertices.sort((a,b) =>a.x-b.x);
  left=vertices[0];
  curr_vertex=left;
  hull.push(curr_vertex);
  nextVertex=vertices[1]; //guess
  check_point=2;
  start=true;
  
}

function draw(){
  if(random_in || (!random_in && start)){
    background(color('#F5F5F5'));
    stroke(color('#ADA8B6'));
    strokeWeight(8);

  for(let p of vertices){
    point(p.x, p.y);
  }
  stroke(color('#573280'));
  fill(227,214,236,100);
  strokeWeight(3);
  //making the hull
  beginShape();
  for(let p of hull){
    vertex(p.x, p.y);
  }
  endShape(CLOSE);
  
  stroke(color('#ADA8B6'));
  strokeWeight(13);
  point(left.x, left.y);
  
  stroke (200,0,255);
  strokeWeight(13);
  point(curr_vertex.x, curr_vertex.y);

  stroke(0,255,0);
  strokeWeight(2);
  line(curr_vertex.x, curr_vertex.y, nextVertex.x, nextVertex.y);

  let checking=vertices[check_point];
  stroke(200);
  line(curr_vertex.x, curr_vertex.y, checking.x, checking.y);

  const a = p5.Vector.sub(nextVertex, curr_vertex);
  const b= p5.Vector.sub(checking, curr_vertex);
  const cross_prod= a.cross(b);
  //console.log(cross_prod.z); // the ans is negative if b is to the left. (outside)
  if (cross_prod.z<0){
    nextVertex=checking;
    next_check_point=check_point;
  }
  check_point++;
  //noLoop();
  if(check_point==vertices.length){
    if(nextVertex==left){
      noStroke();
      user_inp.value('Random: true or false');
      noLoop();
    }
    hull.push(nextVertex);
    curr_vertex=nextVertex;
    check_point=0;
    //vertices.splice(next_check_point,1);
    nextVertex=left;

  }
}
  
}