var Thread = Java.type("java.lang.Thread");
function execute() {
myBot = "barney/commands"
send("NEW_FLOW")
symdef BotID Hexbot3C61054ADD98
MoveToHomePosition
//MoveRelHomeLocal 1, 0, 0, 0,
//MoveRelHomeLocal 2, 0, 0, 0,
//MoveRelHomeLocal 3, 0, 0, 0,
//MoveRelHomeLocal 4, 0, 0, 0,
//MoveRelHomeLocal 5, 0, 0, 0,
//MoveRelHomeLocal 6, 0, 0, 0,
//Doit 1000
MoveRelHomeLocal 1, 0, 2, 0,
Doit 1000
MoveRelHomeLocal 1, 0, 0, 0,
Doit 1000
send("DO_FLOW,$ToeAction,$msecPerFrame")
action.setExitCode(0);
action.setResultText("done.");
out("Parameter parameter set up complete");
return action;
}
function send(cmd){
mqttManager.publish(myTWIPe, cmd);
Thread.sleep(200); 
}
function out(message){
output.print(message);
}
