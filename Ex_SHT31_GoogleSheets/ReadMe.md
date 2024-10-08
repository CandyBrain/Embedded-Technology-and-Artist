<!-- CandyBrain Logo -->
<p align="center">
  <a href="https://candybrain.kr" target="_blank" rel="noopener noreferrer">
    <img src="https://github.com/user-attachments/assets/316ae087-3841-4d35-8a22-fa5a477d0991" alt="Logo_Candybrain_without_Candy_400x89">
  </a>
</p>
<br>
<br>


# ESP32와 연결된 SHT31데이터의 Google Sheets로의 전송 

A `.gitignore` magician in your command line. Joe generates `.gitignore` files from the command line for you.


## Table of Contents
- Prologue
- Introduction
- PART-1: Fingerprint의 획득
- PART-2: Web App ID의 획득
- PART-3: SpreadSheet ID의 획득
- PART-4: Web App 기본코드 수정
- PART-5: ESP32 기본코드 수정
- PART-6: ESP32 소스코드 업로드하기
  - 라이브러리 추가하기
  - CP210x USB 드라이버 설치하기
  - 작동확인


## Prologue
- 이 강좌 수강을 위해서 3개의 파일이 필요
  - Ex_THM_GoogleSheets.ino: ESP32에서 온습도 센서값의 온도값을 읽고 Google Web App으로 전송하는 코드
  - Apps_Script.txt: ESP32에서 받은 데이터를 처리해서 SpreadSheet의 지정된 셀로 전송하는 코드, WebApp에 사용될 스크립트, txt 파일의 내용을 복사하여 사용예정
    Google Sheets의 단일 셀에서 지속적으로 온도값이 업데이트되는 예제코드
  - Apps_Script2.txt
    ESP32에서 받은 데이터를 처리해서 SpreadSheet의 지정된 셀로 전송하는 코드
    WebApp에 사용될 스크립트, txt 파일의 내용을 복사하여 사용예정
    Google Sheets에서 입력되는 데이터들이 지속적으로 쌓이는 예제코드

- **certificate.pem**
    
    fingerprint를 얻기 위해 필요한 google 인증서 파일입니다. fingerprint 획득시 만들 예정입니다.
- 본 폴더에서 파일을 다운로드 받으시면 됩니다. 
- certification.pem 은 fingerprint 획득시 만들 예정입니다.


## Introduction

- 작성예정

## Part1. Fingerprint의 획득
- 

## Part2. Web App ID의 획득
-

## Part3. SpreadSheet ID의 획득
- 

## Part4. Web App 예제코드 수정
- 

## Part5. ESP32 예제코드 수정
- 

## Part6. ESP32 수정코드 컴파일 및 업로드
- 라이브러리 추가하기
- CP210x USB드라이버 설치하기
- 작동확인




### Option 1: Binary

- 작성예정

### Option 2: From source

```bash
$ git clone git@github.com:karan/joe.git
$ cd joe/
$ chmod +x tool.sh
$ ./tool.sh build
```

## Usage

### Commands:

```
ls | list       list all available files
u | update      update all available gitignore files
g | generate    generate gitignore files
```

### Basic usage

```bash
$ joe g java    # outputs .gitignore file for java to stdout
```

To update your `.gitignore` files at any time, simply run:

```bash
$ joe u
```

### Overwrite existing `.gitignore` file

```bash
$ joe g java > .gitignore    # saves a new .gitignore file for java
```

### Append to existing `.gitignore` file

```bash
$ joe g java >> .gitignore    # appends to an existing .gitignore file
```

### Multiple languages

```bash
$ joe g java,node,osx > .gitignore    # saves a new .gitignore file for multiple languages
```

### Create and append to a global .gitignore file

You can also use joe to append to a global .gitignore. These can be helpful when you want to ignore files generated by an IDE, OS, or otherwise.

```bash
$ git config --global core.excludesfile ~/.gitignore # Optional if you have not yet created a global .gitignore
$ joe g OSX,SublimeText >> ~/.gitignore
```

### List all available files

```bash
$ joe ls    # OR `joe list`
```

Output:

> actionscript, ada, agda, android, anjuta, appceleratortitanium, archives, archlinuxpackages, autotools, bricxcc, c, c++, cakephp, cfwheels, chefcookbook, clojure, cloud9, cmake, codeigniter, codekit, commonlisp, composer, concrete5, coq, craftcms, cvs, dart, darteditor, delphi, dm, dreamweaver, drupal, eagle, eclipse, eiffelstudio, elisp, elixir, emacs, ensime, episerver, erlang, espresso, expressionengine, extjs, fancy, finale, flexbuilder, forcedotcom, fortran, fuelphp, gcov, gitbook, go, gradle, grails, gwt, haskell, idris, igorpro, ipythonnotebook, java, jboss, jdeveloper, jekyll, jetbrains, joomla, jython, kate, kdevelop4, kohana, labview, laravel, lazarus, leiningen, lemonstand, libreoffice, lilypond, linux, lithium, lua, lyx, magento, matlab, maven, mercurial, mercury, metaprogrammingsystem, meteor, microsoftoffice, modelsim, momentics, monodevelop, nanoc, netbeans, nim, ninja, node, notepadpp, objective-c, ocaml, opa, opencart, oracleforms, osx, packer, perl, phalcon, playframework, plone, prestashop, processing, python, qooxdoo, qt, r, rails, redcar, redis, rhodesrhomobile, ros, ruby, rust, sass, sbt, scala, scons, scrivener, sdcc, seamgen, sketchup, slickedit, stella, sublimetext, sugarcrm, svn, swift, symfony, symphonycms, tags, tex, textmate, textpattern, tortoisegit, turbogears2, typo3, umbraco, unity, vagrant, vim, virtualenv, visualstudio, vvvv, waf, webmethods, windows, wordpress, xcode, xilinxise, xojo, yeoman, yii, zendframework, zephir

### BONUS ROUND: Alternate version control software

Joe isn't **just** a generator for `.gitignore` files. You can use it and its output wherever a SCM is used.

```bash
$ joe g java > .hgignore
```

## Contributing

#### Bug Reports & Feature Requests

Please use the [issue tracker](https://github.com/karan/joe/issues) to report any bugs or file feature requests.

#### Developing

PRs are welcome. To begin developing, do this:

```bash
$ git clone git@github.com:karan/joe.git
$ cd joe/
$ go run *.go
```

#### `tool.sh`

This is a handy script that automates a lot of developing steps.


```bash
USAGE:
    $ $tool [-h|--help] COMMAND

  EXAMPLES:
    $ $tool deps      Install dependencies for joe
    $ $tool build     Build a binary
    $ $tool run       Build and run the binary
```
