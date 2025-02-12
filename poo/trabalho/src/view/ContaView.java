package view;

import java.awt.BorderLayout;
import java.awt.GridLayout;
import java.awt.event.ActionEvent;
import java.awt.event.ActionListener;

import javax.swing.BorderFactory;
import javax.swing.JButton;
import javax.swing.JFrame;
import javax.swing.JLabel;
import javax.swing.JOptionPane;
import javax.swing.JPanel;
import javax.swing.JScrollPane;
import javax.swing.JTabbedPane;
import javax.swing.JTextArea;
import javax.swing.JTextField;

import controllers.CatalogoController;
import controllers.HospedagemController;
import controllers.MainController;
import dto.ItemDto;
import exception.*;

public class ContaView extends JFrame {

    private static final long serialVersionUID = 3165731873173450125L;
    private final HospedagemController hospedagemController = MainController.getHospedagemController();
    private final CatalogoController catalogoController = MainController.getCatalogoController();

    private JTextField txtHospedagemIdAdd;
    private JTextField txtItemCodigo;
    private JTextField txtQuantidade;
    private JTextField txtHospedagemIdRemove;
    private JTextField txtItemIndex;
    private JTextField txtHospedagemIdList;
    private JTextArea textAreaList;

    public ContaView() {
        setTitle("Conta");
        setSize(600, 400);
        setDefaultCloseOperation(JFrame.DISPOSE_ON_CLOSE);
        setLocationRelativeTo(null);

        JTabbedPane tabbedPane = new JTabbedPane();
        tabbedPane.addTab("Adicionar item a Conta", createAddPannel());
        tabbedPane.addTab("Remover item da conta", createRemovePanel());
        tabbedPane.addTab("Listar Todos", createListPanel());

        add(tabbedPane);
    }

    private JPanel createAddPannel() {
        JPanel addPanel = new JPanel(new GridLayout(5, 2, 10, 10));
        addPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        addPanel.add(new JLabel("ID Hospedagem:"));
        txtHospedagemIdAdd = new JTextField();
        addPanel.add(txtHospedagemIdAdd);

        addPanel.add(new JLabel("Item Codigo (numérico):"));
        txtItemCodigo = new JTextField();
        addPanel.add(txtItemCodigo);

        addPanel.add(new JLabel("Quantidade (numérico):"));
        txtQuantidade = new JTextField();
        addPanel.add(txtQuantidade);

        JButton btnAddItemConta = new JButton("Adicionar item a conta");
        addPanel.add(btnAddItemConta);

        btnAddItemConta.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                addItemConta();
            }
        });

        return addPanel;
    }

    private JPanel createRemovePanel() {
        JPanel removePanel = new JPanel(new GridLayout(3, 2, 10, 10));
        removePanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        removePanel.add(new JLabel("ID Hospedagem:"));
        txtHospedagemIdRemove = new JTextField();
        removePanel.add(txtHospedagemIdRemove);

        removePanel.add(new JLabel("ID item (numérico):"));
        txtItemIndex = new JTextField();
        removePanel.add(txtItemIndex);

        JButton btnRemoveItemConta = new JButton("Remover item da conta");
        removePanel.add(btnRemoveItemConta);

        btnRemoveItemConta.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                removeItemConta();
            }
        });

        return removePanel;
    }

    private JPanel createListPanel() {
        JPanel listPanel = new JPanel(new BorderLayout());
        textAreaList = new JTextArea();
        textAreaList.setEditable(false);
        JScrollPane scrollPaneList = new JScrollPane(textAreaList);
        JPanel inputPanel = new JPanel(new GridLayout(1, 2, 10, 10));
        inputPanel.setBorder(BorderFactory.createEmptyBorder(10, 10, 10, 10));

        inputPanel.add(new JLabel("ID Hospedagem:"));
        txtHospedagemIdList = new JTextField();
        inputPanel.add(txtHospedagemIdList);

        JButton btnList = new JButton("Listar items da conta");
        inputPanel.add(btnList);

        btnList.addActionListener(new ActionListener() {
            public void actionPerformed(ActionEvent e) {
                listItemsConta();
            }
        });

        listPanel.add(inputPanel, BorderLayout.NORTH);
        listPanel.add(scrollPaneList, BorderLayout.CENTER);
        listPanel.add(btnList, BorderLayout.SOUTH);

        return listPanel;
    }

    private void addItemConta() {
        try {
            String idHospedagem = txtHospedagemIdAdd.getText();
            long itemCodigo = Long.parseLong(txtItemCodigo.getText());
            int quantidade = Integer.parseInt(txtQuantidade.getText());
            ItemDto item = catalogoController.getItemDto(itemCodigo);
            hospedagemController.addItemConta(idHospedagem, item, quantidade);
            JOptionPane.showMessageDialog(null, "Item adicionado com sucesso!");
        } catch (HospedagemException | ItemException | TipoAcomodacaoException ex) {
            JOptionPane.showMessageDialog(null, ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void removeItemConta() {
        try {
            String idHospedagem = txtHospedagemIdRemove.getText();
            int itemIndex = Integer.parseInt(txtItemIndex.getText());
            hospedagemController.removeItemConta(idHospedagem, itemIndex);
            JOptionPane.showMessageDialog(null, "Item removido com sucesso!");
        } catch (HospedagemException | TipoAcomodacaoException ex) {
            JOptionPane.showMessageDialog(null, ex.getMessage(), "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NumberFormatException ex) {
            JOptionPane.showMessageDialog(null, "Formato invalido, campos de número deve conter apenas números", "Erro", JOptionPane.ERROR_MESSAGE);
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }

    private void listItemsConta() {
        textAreaList.setText("");
        try {
            String idHospedagem = txtHospedagemIdList.getText();
            String contaList = hospedagemController.listarConta(idHospedagem).toString();
            textAreaList.setText(contaList);
        } catch (HospedagemException | TipoAcomodacaoException ex) {
            textAreaList.setText("Erro ao listar itens: " + ex.getMessage());
        } catch (NullPointerException ex) {
            JOptionPane.showMessageDialog(null, "Todos os campos devem ser preenchidos: ", "Erro", JOptionPane.ERROR_MESSAGE);
        }
    }
}