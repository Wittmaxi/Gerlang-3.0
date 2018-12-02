#include "helpers/parserutil/scope.h"

std::vector<std::tuple<items, std::string>> lexerTokens;
std::vector<std::tuple<items, std::string>> currentLine;
int positionInLexerToken;
int positionInLine;
int lineNumber;
bool hasError;
bool hasMainFunction;
std::vector<scope> scopes;
std::vector<std::string> outCode;
bool isInOutterScope;
std::vector<std::string> totalCode;

scope &outterScope()
{
  return scopes[scopes.size() - 1];
}

items getToken()
{
  if (positionInLine < currentLine.size())
    return std::get<0>(currentLine[positionInLine]);
  return items::VOID;
}

std::string getTInfo()
{
  if (positionInLine < currentLine.size())
    return std::get<1>(currentLine[positionInLine]);
  return "";
}

void wpe(std::string error)
{
  std::cout << "Parser | Fehler, Zeile " << lineNumber << " : " << error << std::endl;
  hasError = true;
}

bool incPos()
{
  positionInLine++;
  return true;
}

void decreaseScope()
{
  if (scopes.size() == 1)
    wpe("\"ende\" bekommen, aber kein Block zum schliessen gefunden.");
  else
  {
    scopes.resize(scopes.size() - 1);
    isInOutterScope = (scopes.size() == 0) ? true : false;
  }
}

#include "helpers/parserutil/parseHelpers.h"

std::string handleFunctionCall()
{
  std::string fcall;
  std::string funName = getTInfo();

  fcall += funName;

  function func(funName, "");

  func = outterScope().getFunc(funName);

  for (auto i : func.inputs)
    incPos();

  return fcall;
}

bool nameExists(std::string name)
{
  return (outterScope().varExists(name) || outterScope().funcExists(name));
}

bool operation()
{
  std::string operationType;
  std::string codeLine;
  if (getToken() == items::IDENT)
    return false;

  if (nameExists(getTInfo()))
    operationType = outterScope().getType(getTInfo());

  incPos();
  if (getToken() != items::DELIM || getTInfo() != "=")
  {
    return false;
    positionInLine--;
  }
  
  bool needsIdentifier = true;
  while (getToken() != items::NEW_LINE)
  {
    wpe(tts(getToken()));
    if (needsIdentifier)
      if (!(getToken() == items::IDENT))
        wpe("\"Identifizierer\" oder \"Dateiende\" erwartet, stattdessen " + tts(getToken()) + " bekommen");
      else if (outterScope().varExists(getTInfo()))
        codeLine += getTInfo();
      else if (outterScope().funcExists(getTInfo()))
        codeLine += handleFunctionCall();
      else
        wpe("Identifizierer " + getTInfo() + " konnte nicht gefunden werden!");
    else if (getToken() == items::DELIM)
      wpe("Operator erwartet, stattdessen " + tts(getToken()) + " bekommen.");
    incPos();
    if (getToken() == items::VOID)
      break;
    needsIdentifier = !needsIdentifier;
  }
}

bool mainFunction()
{
  if (getToken() == items::MAIN_FUNC)
  {
    if (hasMainFunction)
      wpe("Zu viele anfangs-funktionen gefunden.");
    scopes.push_back(scope(outterScope()));
    totalCode.push_back("int main () {");
    hasMainFunction = true;
    incPos();
    return true;
  }
  return false;
}

bool variableDefinition()
{
  variable currVar = parseVariable();
  std::string code = "";
  if (currVar.isInit == true)
  {
    code += currVar.type;
    code += " " + currVar.name;
    outterScope().addVar(std::make_pair(currVar.name, currVar.type));
    if (getToken() == items::DELIM && getTInfo() != "=")
    {
      //TODO
    }
    code += ";";
    totalCode.push_back(code);
  }
  incPos();
  return true;
}

void variablesInFunctionDecl(std::vector<std::tuple<std::string, std::string>> &variables)
{
  while (true)
  {
    variable currentVar;
    currentVar = parseVariable();
    if ((!currentVar.isInit) && (!(getTInfo() == ")")))
      wpe("Variablendeklaration erwartet.");
    else
      variables.push_back(std::make_pair(currentVar.name, currentVar.type));
    if (getTInfo() == ",")
    {
    }
    else if (getTInfo() == ")")
      break;
    else
    {
      wpe("\")\" oder \",\" erwartet, statdessen " + tts(getToken()) + " bekommen.");
      break;
    }
  }
}

bool functionDefinition()
{
  if (!(getToken() == items::FUNCTION_1))
    return false;
  std::string functionName;
  std::vector<std::tuple<std::string, std::string>> variables;
  std::string funcReturnType;

  if (!(incPos()))
    wpe("\"Identifizierer\" erwartet, stattdessen \"Dateiende\" gefunden.");
  if (getToken() == items::IDENT)
    if (identValid(getTInfo()))
      functionName = getTInfo();
    else
      wpe("Funktionsname " + getTInfo() + " ist ungültig oder schon benutzt");
  else
    wpe("\"Identifizierer\" erwartet, stattdessen " + tts(getToken()) + " bekommen.");
  if (!(incPos()))
    wpe("\"(\" erwartet, stattdessen \"Dateiende\" gefunden");
  if (!(getToken() == items::DELIM && getTInfo() == "("))
    wpe("\"(\" erwartet, stattdessen " + tts(getToken()) + " bekommen.");
  if (!incPos())
    wpe("\"Variablendeklaration\" oder \")\" erwartet, stattdessen " + tts(getToken()) + " bekommen.");
  variablesInFunctionDecl(variables);
  if (!(incPos()))
    wpe("\"ergibt\" erwartet, stattdessen \"Dateiende\" bekommen.");
  if (getToken() != items::FUNCTION_2)
    wpe("\"ergibt\" erwartet, statdessen " + tts(getToken()) + " bekommen");
  if (!(incPos()))
    wpe("\"Identifizierer\" erwartet, stattdessen \"Dateiende\" bekommen.");
  if (getToken() != items::IDENT)
    wpe("\"Identifizierer\" erwartet, stattdessen " + tts(getToken()) + " bekommen");
  //incPos();
  funcReturnType = getTInfo();
  outterScope().functions.push_back(function(functionName, funcReturnType));
  scope generatedScope(scopes[scopes.size() - 1], true);
  generatedScope.addVars(variables);
  std::string inputs = "(";
  for (int i = 0; i < variables.size(); i++)
  {
    if (i != 0)
      inputs += ",";
    inputs += (returnTypeName(std::get<1>(variables[i]))) + " ";
    inputs += (returnTypeName(std::get<0>(variables[i])));
  }
  inputs += ")";
  totalCode.push_back(returnTypeName(funcReturnType) + " " + functionName + " " + inputs + " " + "{");
  scopes.push_back(generatedScope);
  isInOutterScope = false;
  return hasError;
}

bool endOfScope()
{
  if (getToken() == items::SCOPE_END)
  {
    totalCode.push_back("}");
    decreaseScope();
    incPos();
    return true;
  }
  return false;
}

bool innerScopeCalls()
{
  if (!isInOutterScope)
    if (endOfScope() || operation())
      return true;
  return false;
}

void beginOfFile()
{
  isInOutterScope = true;
  while ((positionInLexerToken < lexerTokens.size()) && !(hasError))
  {
    getLineTokens();
    lineNumber++;
    if (mainFunction() || functionDefinition() || innerScopeCalls() || variableDefinition())
    {
      if (!hasError)
        if (positionInLine < currentLine.size())
          wpe("\"Neue Zeile\" erwartet, stattdessen " + tts(getToken()) + " bekommen.");
    }
    else
      wpe("Unerwarteterweise " + tts(getToken()) + " bekommen.");
  }
  if (!hasMainFunction)
    wpe("Keine anfangs-funktion im Programm gefunden.");
  for (auto i : totalCode)
    std::cout << i << std::endl;
}

bool parse(std::vector<std::tuple<items, std::string>> input)
{
  lexerTokens = input;
  scope outterScope;
  scopes.push_back(outterScope);
  beginOfFile();
}
