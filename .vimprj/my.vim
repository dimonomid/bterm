
" detect path to .vimprj folder
let s:sVimprjPath = expand('<sfile>:p:h')

let g:proj_project_filename=s:sVimprjPath.'/.vimprojects'

let &tabstop = 4
let &shiftwidth = 4

let g:indexer_ctagsDontSpecifyFilesIfPossible = 1
"let g:indexer_enableWhenProjectDirFound = 0
"let g:indexer_ctagsJustAppendTagsAtFileSave = 1

" specify .indexer_files to use for Indexer
let g:indexer_indexerListFilename = s:sVimprjPath.'/.indexer_files'
"let g:indexer_useSedWhenAppend = 0
"let g:indexer_projectsSettingsFilename = s:sVimprjPath.'/.vimprojects'
"let g:indexer_projectName = 'Osa'


" ctags -R --c++-kinds=+p --fields=+iaS --extra=+q /usr/share/qt4
"set tags+=C:\NokiaQtSDK\QtSources\4.6.3\tags

"exe 'set tags+='.$MACHINE_LOCAL_CONF__PATH__QT_DOC_TAGS

let g:indexer_ctagsCommandLineOptions = '--c++-kinds=+p+l --c-kinds=+l --fields=+iaS --extra=+q'



" -------------- настраиваем сборку файлов из vim ----------------

" Путь до build директории qt-creator: для того, чтобы
" инклудить ui-файлы. Эти ui_xxx.h файлы размещаются как раз в
" build-директории.
let s:sProjectName = 'dterminal_qt'
let s:sBuildPath = $INDEXER_PROJECT_ROOT.'/../build-hterm-Desktop_Qt_5_5_0_GCC_32bit-Debug'

if isdirectory(s:sBuildPath)
   let s:o_dir = s:sBuildPath.'/compiled_in_vim'

   if !isdirectory(s:o_dir)
      call mkdir(s:o_dir, "p")
   endif
else
   let s:o_dir = '.'
endif


"if (has('win32') || has('win64'))
   "let &makeprg = MakeprgGenerate(s:sBuildPath.'/Makefile.Release', 'qt_makefile', {})
"else
   "let &makeprg = MakeprgGenerate(s:sBuildPath.'/Makefile', 'qt_makefile', {})
"endif


let g:indexer_handlePath = 0
if (has('win32') || has('win64'))
   call CheckNeededSymbols(
            \  "The following items needs to be defined in your vimfiles/machine_local_conf/current/variables.vim file to make things work: ",
            \  "",
            \  [
            \     '$MACHINE_LOCAL_CONF__PATH__MINGW_INCLUDE',
            \  ]
            \  )


   call envcontrol#set_project_file(s:sBuildPath.'/Makefile.Release', 'makefile', {
            \        'parser_params': {
            \           '-o' : simplify(s:o_dir.'/%:t:r.o'),
            \        },
            \        'handle_clang' : 1,
            \        'add_paths' : [
            \           $MACHINE_LOCAL_CONF__PATH__MINGW_INCLUDE,
            \           $MACHINE_LOCAL_CONF__PATH__MINGW_INCLUDE.'/c++',
            \           $MACHINE_LOCAL_CONF__PATH__MINGW_INCLUDE.'/c++/mingw32',
            \        ],
            \  })
else
   call envcontrol#set_project_file(s:sBuildPath.'/Makefile', 'makefile', {})
endif


let s:sProjectPath = simplify(s:sVimprjPath.'/..')

let g:vimwiki_list[0] =
         \  {
         \     'maxhi': 0,
         \     'css_name': 'style.css',
         \     'auto_export': 0,
         \     'diary_index': 'diary',
         \     'template_default': '',
         \     'nested_syntaxes': {},
         \     'diary_sort': 'desc',
         \     'path': s:sProjectPath.'/stuff/vimwiki/',
         \     'diary_link_fmt': '%Y-%m-%d',
         \     'template_ext': '',
         \     'syntax': 'default',
         \     'custom_wiki2html': '',
         \     'index': 'index',
         \     'diary_header': 'Diary',
         \     'ext': '.wiki',
         \     'path_html': '',
         \     'temp': 0,
         \     'template_path': '',
         \     'list_margin': -1,
         \     'diary_rel_path': 'diary/'
         \  }


