# vim
* :e 파일명 => 다른파일을 오픈한다.
* :w 파일명 => 다른이름으로 저장한다.
* gg => 문서 맨처음으로 이동한다.
* G => 문서 맨 마지막으로 이동한다.
* yy -> 한줄복사
* p -> 붙여넣기
* D -> 한 행의 커서 뒤 모든 글자 지운다.
* ctrl+r => 되살리기
* cw => 한단어 지워지고 자동으로 i 모드.
* v => 현재 커서로 부터 블록 가능.
* ctrl+v => 열로 블록
* shift+v => 한 라인 단위로 블록
* 모든거 블록후 = 누르면 => 자동으로 들여쓰기를 맞추어준다.
* :%s/old/new/g => old를 new로 바꾼다.(gc는 확인하면서)
* /찾을단어 => 하이라이트됨 (기본설정안할 땐? )

# vim 기본설정
#### $ vim ~/.vimrc
* set number
* syntax on
* set autoindent
* set cindent
* set smartindent
* set tabstop=4
* set shiftwidth=4
* set softtabstop=4
* set hlsearch
* set expandtab autocmd FileType make setlocal noexpandtab

”줄번호 on ”syntax highlight 기능 on ”자동 인덴트 ”c언어 자동 인덴트
”탭키의 너비 ”자동 인덴트할때 너비
”검색 하이라이트 “탭키를 white space로 처리 “Makefile 수정시 예외설정

# vim 스킨 변경
* https://vim.sourceforge.io/    에서 원하는 스킨 다운로드한다.
```
$ cd ~/Downloads/ $ curl https://vim.sourceforge.io/scripts/download_script.php?src_ id=25026 -o papercolor-theme-0.8.tar
$ tar xvfz papercolor-theme-0.8.tar
$ mkdir ~/.vim $ mv ~/Downloads/papercolor-theme-0.8/colors/ ~/.vim
후
$ vim ~/.vimrc  에
set background=dark    
set t_Co=256
colorscheme PaperColor
```
# vim 에서 man 단축키 설정
```
$ vim ~/.vimrc  에
func! Man()
  let sm = expand("<cword>")
  exe "!man -S 2:3:4:5:6:7:8:9:tcl:n:l:p:o ".sm
endfunc
nmap ,ma :call Man()<CR><CR>

//원하는 함수에서 ,ma를 누르면 man창이 뜬다.  
```
