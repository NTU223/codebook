set nocp mouse=a bs=2
set nu hls ru ls=2 cul sb spr
set ai ts=4 sw=4 sts=4 et sta
set nobk noswf ar
set noea noeb novb t_vb=

sy on
hi CursorLine ctermbg=233
hi LineNr     ctermfg=236
hi Search     ctermbg=52
hi MatchParen ctermbg=234

 map o oo<bs>
 map O OO<bs>
imap <cr> <cr>a<bs>

vmap > >gv
vmap < <gv
 map <f9>      :w<cr>:!g++ -lm -std=c++11 -o %:r -Wall %<cr>
imap <f9> <esc>:w<cr>:!g++ -lm -std=c++11 -o %:r -Wall %<cr>
 map <f1> <esc>
imap <f1> <esc>

map \\ :silent! /asdfadfeifj<cr>
map \x mzHmx:silent! :%s/[ \t][ \t]*$//g<CR>`xzt`z\\
