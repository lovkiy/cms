<?php

/**
 * Description of menumodel
 *
 * @author Alex
 */
class menumodel {
    
    public function showMenu($page,$vid,$lang_id){
        
        $menu_id = db::GetOne("SELECT block_id FROM pages_views
                                WHERE p_id={$page}
                                    AND l_id={$vid}
                                        AND lang_id={$lang_id}");
        
        $data = $this->_extMenu($menu_id);
        return $data;
    }
    private function _extMenu($menu_id){
        $query = db::GetAll("SELECT mp.id,mp.name,mp.pid,p.url,p.main 
                             FROM menus_pages mp
                             JOIN pages p ON p.id=mp.page_id
                             WHERE mp.menu_id=$menu_id
                             AND mp.active=1
                             ORDER BY mp.pid ASC, mp.id ASC");
        
        for ($i = 0, $c = count($query); $i < $c; $i++)
        {
            $new_arr[$query[$i]['pid']][] = $query[$i];
        }
                
      return $new_arr;       
    } 
}

?>
