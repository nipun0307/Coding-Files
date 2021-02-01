let inp_m;
let r_n=0, b_n=0, g_n=0
function setup() {
  createCanvas(750, 750);
  background(230);
  create_rec();
  inp_m=createInput('division per side',[int]);
  inp_m.position(width+2, height/2);
  let do_enter=createButton("ENTER");
  do_enter.position(inp_m.x+inp_m.width+1, inp_m.y+0.4);
  do_enter.mousePressed(do_grid);
  // let inp=createInput('division per side');
  // inp.position(width+10, height/2);
  // let n=int(inp.value());
  // inp.changed(do_grid(n));
  noLoop();
}

function create_rec(){
  noStroke();
  let pt=float(width)/4;
  let alpha=200;
  fill(255,0,0,alpha);
  rectMode(CENTER);
  square(pt*1,80,50);

  fill(0,255,0,alpha);
  square(pt*2,80,50);
  fill(0,0,255,alpha);
  square(pt*3,80,50);
  
}

function do_grid(){
  let n=int(inp_m.value());
  console.log(n);
  background(230);
  create_rec();
  let grid= new create_grid((width-500)/2, 200, 500, n);
  grid.create(0,0,0,255,1);
}


function draw() {
}



class create_grid{
  constructor(x, y, side, n){
    this.x=x;
    this.y=y;
    this.side=side;
    this.n=n;
  }
  create(r, g, b, alpha, str_wt){
    noFill();
    stroke(r,g,b,alpha);
    strokeWeight(str_wt);
    let each=float(this.side)/this.n;
    for(let i=0; i<this.n; i++)
      for(let j=0; j<this.n; j++)
        square(this.x+(j*each), this.y+(i*each), each);
  }
}
