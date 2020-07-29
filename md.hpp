#include <bits/stdc++.h>
#include "md4c-html.h"
#include "str.h"
/* Global options. */
static unsigned parser_flags=0;
#ifndef MD4C_USE_ASCII
    static unsigned renderer_flags=MD_HTML_FLAG_DEBUG | MD_HTML_FLAG_SKIP_UTF8_BOM;
#else
    static unsigned renderer_flags=MD_HTML_FLAG_DEBUG;
#endif
struct membuffer{
    char* data;
    size_t asize;
    size_t size;
};
static void membuf_init(struct membuffer* buf,MD_SIZE new_asize){
    buf->size=0;
    buf->asize=new_asize;
    buf->data=(char*)malloc(buf->asize);
}
static void membuf_grow(struct membuffer* buf,size_t new_asize){
    buf->data=(char*)realloc(buf->data,new_asize);
    buf->asize=new_asize;
}
static void membuf_append(struct membuffer* buf,const char* data,MD_SIZE size){
    if(buf->asize<buf->size+size)
        membuf_grow(buf,buf->size+buf->size/2+size);
    memcpy(buf->data+buf->size,data,size);
    buf->size += size;
}
static void process_output(const MD_CHAR* text,MD_SIZE size,void*userdata){
    membuf_append((struct membuffer*)userdata,text,size);
}
const membuffer markdown(const char*in){
    MD_SIZE n;
    membuffer buf_in;
    membuffer buf_out;
    buf_in.data=(char *)in;
    buf_in.size=strlen(in);
    membuf_init(&buf_out,buf_in.size+buf_in.size/8+64);    
    md_html(buf_in.data,buf_in.size,process_output,(void*) &buf_out,parser_flags,renderer_flags);
    return buf_out;
}
std::string str_markdown(const char*in){
    membuffer res=markdown(in);
    return std::string(res.data,res.data+res.size);
}
void set_ext(){
    // parser_flags=MD_DIALECT_COMMONMARK;
    // parser_flags=MD_DIALECT_GITHUB;
    // renderer_flags |= MD_HTML_FLAG_VERBATIM_ENTITIES;
    // parser_flags |= MD_FLAG_PERMISSIVEATXHEADERS;
    // parser_flags |= MD_FLAG_NOINDENTEDCODEBLOCKS;
    // parser_flags |= MD_FLAG_NOHTMLBLOCKS;
    // parser_flags |= MD_FLAG_NOHTMLSPANS;
    // parser_flags |= MD_FLAG_NOHTML;
    // parser_flags |= MD_FLAG_COLLAPSEWHITESPACE;
    // parser_flags |= MD_FLAG_PERMISSIVEURLAUTOLINKS;
    // parser_flags |= MD_FLAG_PERMISSIVEWWWAUTOLINKS;
    // parser_flags |= MD_FLAG_PERMISSIVEEMAILAUTOLINKS;
    // parser_flags |= MD_FLAG_PERMISSIVEAUTOLINKS;
    parser_flags|=MD_FLAG_TABLES;
    // parser_flags |= MD_FLAG_STRIKETHROUGH;
    parser_flags|=MD_FLAG_LATEXMATHSPANS;
    // parser_flags |= MD_FLAG_WIKILINKS;
    // parser_flags |= MD_FLAG_TASKLISTS;
    // parser_flags |= MD_FLAG_UNDERLINE;
}