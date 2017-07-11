<?php if ( ! defined('BASE')) exit('Нету прямого доступа к данному скрипту');

/**
 * Description of meta
 *
 * @author Alex
 */

class meta {
    private static function _getLangId(){
        $lang_id = db::GetOne("SELECT id FROM languages WHERE code= '".LANGDIR."'");
        return $lang_id;
    }
    public static function GetMeta($page_id,$url){
     
     $lang_id = self::_getLangId();              
     $meta = db::GetRow("SELECT meta_title as title,meta_description as description,
                          meta_keywords as keywords FROM pages_description 
                          WHERE p_id={$page_id} AND lang_id = {$lang_id}");         
    
     
     $modules = db::GetAll("SELECT l.mm FROM layouts l
                            JOIN pages p ON p.temp_id = l.template 
                            WHERE p.id = {$page_id}");                          
                
     foreach ($modules as $key=>$mod):
         if($mod['mm']==12):
             switch($url[0]):
                case 'group':
                    $meta = db::GetRow("SELECT meta_title as title,meta_description as description,
                                        meta_keywords as keywords 
                                        FROM catalogue_groups_description 
                                        WHERE cat_group_id={$url[1]} AND lang_id = {$lang_id}");
                    return $meta;                    
                    break;
                case 'item':
                    $meta = db::GetRow("SELECT meta_title as title,meta_description as description,
                                        meta_keywords as keywords 
                                        FROM catalogue_products p 
                                        JOIN catalogue_relationship r ON r.prod_id = p.id
                                        WHERE item_id={$url[1]} AND lang_id = {$lang_id}");
                    return $meta;                    
                    break;
             endswitch;
         endif;
     endforeach;                      
     
     return $meta;
    }
    
}

?>
