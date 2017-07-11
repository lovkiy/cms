<?php
/**
 * Description of pagesmodel
 *
 * @author Alex
 */
class pagesmodel {
    private $_lang_id;
    
    public function __construct() {
        $this->_lang_id = db::GetOne("SELECT id FROM languages WHERE code= '".LANGDIR."'");
    }    
   
    public function getLang(){
        $query = db::GetAll("SELECT id,code FROM languages WHERE enabled=1 AND id=".$this->_lang_id."
                             UNION
                             SELECT id,code FROM languages WHERE enabled=1 AND id!=".$this->_lang_id);        
        return $query;
    }
    /*
     * Метод который овечает за создание странички 
     * проэкта
     */
    final public function createPage($post){
        $url = toAscii(rus2translit(trim($post['name'])));
        $pageName = db::quote(trim($post['name']));
        $pageTempId = $post['layout'];
        $max_sort = db::GetOne("SELECT MAX(sort) FROM pages");
        db::execute("INSERT INTO pages SET temp_id ={$pageTempId},url='{$url}',sort = ".($max_sort+1));       
        $pageId = db::lastInsertId();
        db::execute("INSERT INTO pages_description (p_id,lang_id,name) 
                     VALUES ({$pageId},{$this->_lang_id},{$pageName})");     
    }
    /*
     * Метод возвращающий список страниц 
     * сиключая страницы админпанели...
     * TODO: Сделать возможность редактирования и страницы админ панели 
     * из пользователя суперадмина.. "во"
     *ЗЫ: Возможно это и не понадобится...
     */
    
    final public function pageList(){
       
       $query = db::GetAll("SELECT p.id,p.pid,pd.name,p.main,p.type,p.active,pd.lang_id 
                            FROM pages p
                            JOIN pages_description pd ON pd.p_id = p.id
                            WHERE p.id!=1 AND lang_id = {$this->_lang_id} ORDER BY p.main DESC");        
        
        
        for ($i = 0, $c = count($query); $i < $c; $i++){
            $tid = db::GetOne("SELECT temp_id FROM pages  WHERE id={$query[$i]['id']} ");                          
                               
            $views = db::GetAll("SELECT l.id AS lid, mv.id, mv.name, m.name AS module, l.description 
                                 FROM module_views mv
                                 JOIN layouts l ON l.mv_id = mv.id
                                 JOIN module m ON m.id = mv.module
                                 WHERE l.template={$tid}");
            $query[$i]['views'] = $views; 
            $new_arr[$query[$i]['pid']][] = $query[$i];
        }
       
        return $new_arr;
    }
    public function setMain($page){
        
       db::execute("UPDATE pages SET main=0");
       db::execute("UPDATE pages SET main=1 WHERE id={$page}");
    }
    public function getPageInfo($page_id){
        
        $query['page'] = db::GetALL("SELECT p.id,pd.name,p.url,pd.meta_title as title,
                                     pd.meta_keywords as keywords,pd.meta_description as description 
                                     FROM pages p
                                     LEFT JOIN pages_description pd ON pd.p_id = p.id 
                                     WHERE p.id={$page_id} AND pd.lang_id = {$this->_lang_id}
                                     UNION
                                     SELECT p.id,pd.name,p.url,pd.meta_title as title,
                                     pd.meta_keywords as keywords,pd.meta_description as description 
                                     FROM pages p
                                     LEFT JOIN pages_description pd ON pd.p_id = p.id 
                                     WHERE p.id={$page_id} AND pd.lang_id!= {$this->_lang_id}");
       return $query;
    }
    public function updatePage($page_id){
        $name = db::quote($_POST['pagename']);
        $url = db::quote($_POST['url']);
        $old_url = db::GetOne("SELECT url FROM pages WHERE id = {$page_id}");
        if($_POST['url']!==$old_url):
            db::execute("UPDATE pages SET url={$url} WHERE id={$page_id}"); 
            db::execute("INSERT INTO redirects (url,redirect) VALUES ('{$old_url}',{$url})");
            db::execute("UPDATE redirects SET redirect = {$url} WHERE redirect='{$old_url}'");
        endif;
          
        
        foreach ($_POST['pages'] as $key=>$val):
           $name = db::quote(strip_tags(trim($val['name']))); 
           $title = db::quote(strip_tags(trim($val['title'])));
           $keywords = db::quote(strip_tags(trim($val['keywords'])));
           $description = db::quote(strip_tags(trim($val['description'])));
           
           db::execute("INSERT INTO pages_description (p_id,lang_id,name,meta_title,meta_description,meta_keywords) 
                        VALUES ({$page_id},{$key},{$name},{$title},{$description},{$keywords}) 
                        ON DUPLICATE KEY UPDATE name = {$name},meta_title = {$title},
                        meta_description = {$description},meta_keywords = {$keywords} ");
          
        endforeach;
    }    
    public function hidePage($page_id){        
        db::execute("UPDATE pages SET active=0 WHERE id={$page_id}");  
    }
    public function showPage($page_id){        
        db::execute("UPDATE pages SET active=1 WHERE id={$page_id}");  
    }
    public function createFolder(){
        $name = db::quote($_POST['name']);
        $max_sort = db::GetOne("SELECT MAX(sort) FROM pages");
        db::execute("INSERT INTO pages (type,sort) VALUES (2,".($max_sort+1).")"); 
        $fold_id = db::lastInsertId();
        db::execute("INSERT INTO pages_description (p_id,lang_id,name) VALUES ({$fold_id},{$this->_lang_id},{$name})");
        db::execute("UPDATE pages SET url='folder_{$fold_id}' WHERE id={$fold_id}");
    }
    public function moveToFolder($page,$folder){
        db::execute("UPDATE pages SET pid={$folder} WHERE id={$page}");        
    }
    public function folderList($folder){
        $query = db::GetAll("SELECT p.id,pd.name FROM pages p
                             JOIN pages_description pd ON pd.p_id = p.id
                             WHERE p.type=2 AND p.id!={$folder} AND pd.lang_id={$this->_lang_id}");
        return $query;
    }
    public function dellFolder($fold_id){
        db::execute("UPDATE pages SET pid=0 WHERE pid={$fold_id}");
        db::execute("DELETE FROM pages WHERE id={$fold_id}");
    }
    public function dellFolderAll($fold_id){
        $query = db::GetAll("SELECT id FROM pages WHERE pid = {$fold_id}");
        for($x=0;$x<sizeof($query);$x++):
             db::execute("DELETE FROM pages_views WHERE p_id = {$query[$x]['id']}");
             db::execute("DELETE FROM pages WHERE id = {$query[$x]['id']}");
             db::execute("DELETE FROM menus_pages WHERE page_id = {$query[$x]['id']}");
             db::execute("DELETE FROM pages_description WHERE p_id = {$query[$x]['id']}");
        endfor;       
        db::execute("DELETE FROM pages WHERE id = {$fold_id}");         
    }
    public function dellPage($page_id){
        db::execute("DELETE FROM pages WHERE id={$page_id}");
        db::execute("DELETE FROM pages_views WHERE p_id = {$page_id}");
        db::execute("DELETE FROM menus_pages WHERE page_id = {$page_id}");
        db::execute("DELETE FROM pages_description WHERE p_id = {$page_id}");
    }
}

?>
