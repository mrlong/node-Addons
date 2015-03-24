var addon = require('./build/Release/addon');

console.log(addon.hello()); // 'world'

console.log( 'This should be eight:', addon.add(6,5) );

addon.ord('ssss困困地地要地地要',function(msg){
  console.log(msg); // 'hello world'
});