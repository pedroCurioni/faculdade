package view;

import controllers.CatalogoController;
import controllers.MainController;
import dto.CategoriaDto;
import exception.CategoriaException;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.Set;

public class CategoriaView extends JFrame {

    private static final long serialVersionUID = -2176037146780695559L;
    private final CatalogoController catalogoController = MainController.getCatalogoController();
    private JTextField txtNome;
    private JTextArea textAreaList;

    public CategoriaView() {
        setTitle("Categoria");
        setSize(500, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();

        tabbedPane.addTab("Criar Categoria", createCreatePanel());
        tabbedPane.addTab("Listar Todos", createListPanel());

        add(tabbedPane);
    }

    private JPanel createCreatePanel() {
        JPanel createPanel = new JPanel(new GridLayout(2, 2, 10, 10));
        createPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        createPanel.add(new JLabel("Nome:"));
        txtNome = new JTextField();
        createPanel.add(txtNome);

        JButton btnCreate = new JButton("Criar Categoria");
        createPanel.add(btnCreate);

        btnCreate.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                createCategoria();
            }
        });

        return createPanel;
    }

    private JPanel createListPanel() {
        JPanel listPanel = new JPanel(new BorderLayout());
        textAreaList = new JTextArea();
        textAreaList.setEditable(false);
        JScrollPane scrollPaneList = new JScrollPane(textAreaList);
        JButton btnList = new JButton("Listar Todos");

        btnList.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                listCategorias();
            }
        });

        listPanel.add(scrollPaneList, BorderLayout.CENTER);
        listPanel.add(btnList, BorderLayout.SOUTH);

        return listPanel;
    }

    private void createCategoria() {
        try {
            String nome = txtNome.getText();
            CategoriaDto categoriaDto = new CategoriaDto(nome);
            catalogoController.criarCategoria(categoriaDto);
            JOptionPane.showMessageDialog(null, "Categoria criada com sucesso!");
        } catch (CategoriaException ex) {
            JOptionPane.showMessageDialog(null, ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void listCategorias() {
        textAreaList.setText("");
        Set<String> categorias = catalogoController.getCategorias();
        for (String nome : categorias) {
            textAreaList.append(nome + "\n");
        }
    }
}