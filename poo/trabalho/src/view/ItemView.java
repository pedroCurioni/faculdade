package view;

import controllers.CatalogoController;
import controllers.MainController;
import dto.ItemDto;
import exception.CategoriaException;
import exception.ItemException;

import javax.swing.*;
import java.awt.*;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;
import java.util.List;

public class ItemView extends JFrame {

    private static final long serialVersionUID = 4187850695178283232L;
    private final CatalogoController catalogoController = MainController.getCatalogoController();

    private JTextField txtNomeCategoria;
    private JTextField txtCodigo;
    private JTextField txtDescricao;
    private JTextField txtPreco;
    private JTextField txtNomeCategoriaList;
    private JTextArea textAreaList;
    private JTextField txtCodigoGet;
    private JTextArea textAreaGet;

    public ItemView() {
        setTitle("Item");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Criar Item", createCreatePanel());
        tabbedPane.addTab("Listar", createListPanel());
        tabbedPane.addTab("Obter Item", createGetPanel());

        add(tabbedPane);
    }

    private JPanel createCreatePanel() {
        JPanel createPanel = new JPanel(new GridLayout(5, 2, 10, 10));
        createPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        createPanel.add(new JLabel("Nome Categoria:"));
        txtNomeCategoria = new JTextField();
        createPanel.add(txtNomeCategoria);

        createPanel.add(new JLabel("Codigo (numérico):"));
        txtCodigo = new JTextField();
        createPanel.add(txtCodigo);

        createPanel.add(new JLabel("Descricao:"));
        txtDescricao = new JTextField();
        createPanel.add(txtDescricao);

        createPanel.add(new JLabel("Preco (numérico):"));
        txtPreco = new JTextField();
        createPanel.add(txtPreco);

        JButton btnCreate = new JButton("Criar Item");
        createPanel.add(btnCreate);

        btnCreate.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                createItem();
            }
        });

        return createPanel;
    }

    private JPanel createListPanel() {
        JPanel listPanel = new JPanel(new BorderLayout());
        textAreaList = new JTextArea();
        textAreaList.setEditable(false);
        JScrollPane scrollPaneList = new JScrollPane(textAreaList);
        JPanel inputPanel = new JPanel(new GridLayout(1, 2, 10, 10));
        inputPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        inputPanel.add(new JLabel("Nome Categoria (Opcional):"));
        txtNomeCategoriaList = new JTextField();
        inputPanel.add(txtNomeCategoriaList);

        JButton btnList = new JButton("Listar");
        inputPanel.add(btnList);

        btnList.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                listItems();
            }
        });

        listPanel.add(inputPanel, BorderLayout.NORTH);
        listPanel.add(scrollPaneList, BorderLayout.CENTER);
        listPanel.add(btnList, BorderLayout.SOUTH);

        return listPanel;
    }

    private JPanel createGetPanel() {
        JPanel getPanel = new JPanel(new BorderLayout());
        JPanel inputGetPanel = new JPanel(new GridLayout(2, 2, 10, 10));
        inputGetPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        inputGetPanel.add(new JLabel("Codigo (numérico):"));
        txtCodigoGet = new JTextField();
        inputGetPanel.add(txtCodigoGet);

        JButton btnGet = new JButton("Obter Item");
        inputGetPanel.add(btnGet);

        getPanel.add(inputGetPanel, BorderLayout.NORTH);

        textAreaGet = new JTextArea();
        textAreaGet.setEditable(false);
        getPanel.add(new JScrollPane(textAreaGet), BorderLayout.CENTER);

        btnGet.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                getItem();
            }
        });

        return getPanel;
    }

    private void createItem() {
        try {
            String nomeCategoria = txtNomeCategoria.getText();
            long codigo = Long.parseLong(txtCodigo.getText());
            String descricao = txtDescricao.getText();
            double preco = Double.parseDouble(txtPreco.getText());
            ItemDto itemDto = new ItemDto(codigo, descricao, preco);
            catalogoController.criarItens(nomeCategoria, itemDto);
            JOptionPane.showMessageDialog(null, "Item criado com sucesso!");
        } catch (ItemException | CategoriaException ex) {
            JOptionPane.showMessageDialog(null, "Erro: " + ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void listItems() {
        textAreaList.setText("");
        try {
            String nomeCategoria = txtNomeCategoriaList.getText();
            if (nomeCategoria.isEmpty()) {
                for (Long codigo : catalogoController.getItens()) {
                    textAreaList.append(codigo + "\n");
                }
            } else {
                List<ItemDto> itens = catalogoController.getItensByCategoria(nomeCategoria);
                for (ItemDto itemDto : itens) {
                    textAreaList.append(itemDto.getCodigo() + " - " + itemDto.getDescricao() + "\n");
                }
            }
        } catch (CategoriaException ex) {
            textAreaList.append("Erro: " + ex.getMessage() + "\n");
        }
    }

    private void getItem() {
        try {
            long codigo = Long.parseLong(txtCodigoGet.getText());
            ItemDto itemDto = catalogoController.getItemDto(codigo);
            textAreaGet.setText(itemDto.toString());
        } catch (ItemException ex) {
            textAreaGet.setText("Erro ao obter item: " + ex.getMessage());
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }
}