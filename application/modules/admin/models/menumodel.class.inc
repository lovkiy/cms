<?php

/**
 * Description of menumodel
 *
 * @author Alex
 */
class menumodel {
    private $_lang_id;
    
    public function __construct() {
        $this->_lang_id = db::GetOne("SELECT id FROM languages WHERE code= '".LANGDIR."'");
    } 
    public function blocks($param){
     
        if($param['params'][4]=='on'){
            db::execute("INSERT INTO pages_views (p_id,l_id,block_id) 
                          VALUES ({$param['params'][2]},{$param['params'][3]},{$param['params'][5]})");                         
            
        }elseif($param['params'][4]=='off'){            
            db::execute("DELETE FROM pages_views 
                         WHERE p_id={$param['params'][2]} 
                             AND l_id={$param['params'][3]}  
                                 AND block_id={$param['params'][5]}");
        }elseif($param['params'][4]=='lang'){
            db::execute("UPDATE pages_views SET lang_id={$param['params'][6]}
                         WHERE p_id={$param['params'][2]}
                             AND l_id={$param['params'][3]}
                                 AND block_id={$param['params'][5]}");            
        }
        
        $menu_id = db::GetAll("SELECT block_id,lang_id FROM  pages_views
                             WHERE p_id={$param['params'][2]} AND l_id = {$param['params'][3]}");
        
        for($x=0;$x<sizeof($menu_id);$x++):
            $id[] = $menu_id[$x]['block_id']; 
            $lang_id[$menu_id[$x]['block_id']] = $menu_id[$x]['lang_id'];
        endfor;                     
                             
        $query = db::GetAll("SELECT id,name FROM menus");                     
        $data['menu_id'] = $id;
        $data['lang_id'] = $lang_id;
        $data['menus'] = $query;
        if($query):
            return $data;
        endif;
        
    }
    public function createMenu($name){
        $name = db::quote($name);
        db::execute("INSERT INTO menus (name) VALUES ({$name})");  
        $id = db::lastInsertId();        
    }
    public function createFullMenu($name){
        $name = db::quote($name);
        db::execute("INSERT INTO menus (name) VALUES ({$name})");
    }
    public function menuList(){
        $query = db::GetAll("SELECT id,name FROM menus ");
        return $query;
    }
    public function getMenuName($id){
        $query = db::GetOne("SELECT name FROM menus WHERE id={$id}");
        return $query;
    }
    public function updateMenu($id,$name){
        $name = db::quote($name);
        db::execute("UPDATE menus SET name={$name} WHERE id={$id}");
    }
    public function getPageForMenu(){
        $query = db::GetAll("SELECT p.id,pd.name FROM pages p 
                             JOIN pages_description pd ON pd.p_id = p.id
                             WHERE p.id!=1 AND p.type!=2 AND pd.lang_id={$this->_lang_id}");
        return $query;
    }
    public function addPageInMenu($menu_id){
        
        foreach ($_POST['page'] as $page=>$value):
            if(isset($value['id'])):
                 $name = db::quote($value['name']);
                 db::execute("INSERT INTO menus_pages (page_id,menu_id,name,pid) 
                              VALUES ({$value['id']},{$menu_id},{$name},0)");
            endif;           
        endforeach;
    }
    public function getPageInMenu($menu_id){
        $query = db::GetAll("SELECT mp.id,mp.pid,mp.name,pd.name as pagename ,mp.active 
                             FROM menus_pages mp                             
                             JOIN pages_description pd ON pd.p_id = mp.page_id
                             WHERE menu_id={$menu_id} AND pd.lang_id={$this->_lang_id}
                                 ORDER BY mp.pid");
                             
        for ($i = 0, $c = count($query); $i < $c; $i++){
            $new_arr[$query[$i]['pid']][] = $query[$i];
        }                     
        return $new_arr;
    }
    public function dellFromMenu($page_id){
        db::execute("DELETE FROM menus_pages WHERE id={$page_id}");
    }
    public function getMenuPage($page_id){
        $query = db::GetOne("SELECT name FROM menus_pages WHERE id={$page_id}");
        return $query;
    }
    public function updatePageMenu($page_id,$name){
        $name = db::quote($name);
        db::execute("UPDATE menus_pages SET name ={$name} WHERE id={$page_id}");
    }
    public function menuPagesList($menu_id,$menu_page_id){       
        $query = db::GetAll("SELECT id,name FROM menus_pages 
                             WHERE menu_id={$menu_id} AND id!={$menu_page_id}");
        return $query;
    }
    public function moveMenuPage($id_moved,$id_move_in){
        db::execute("UPDATE menus_pages SET pid={$id_move_in} WHERE id={$id_moved}");
    }
}

?>
