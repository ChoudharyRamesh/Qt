.import "js2.js" as Js2

function func()
{
 console.log("hello there");
}

function func2(X,Y) {
  return X+Y;
}

//calling Js2 functions

function temp(X,Y)
{
    return Js2.func3(X,Y);
}


//Qt include ( copy all content of that file here , like c++ include )
Qt.include("js3.js")
